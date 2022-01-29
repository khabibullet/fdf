/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/01/29 22:24:40 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fdf_lib.h"
#include "src/ft_split.c"
#include "src/ft_strlcpy.c"
#include "src/get_next_line.c"
#include "src/get_next_line_utils.c"
#include "src/ft_atoi.c"
#include "src/ft_isdigit.c"

void	def_vars(t_mlx	*gen)
{
	gen->map_name = "maps/42.fdf";
	gen->win_h = 800;
	gen->win_w = 700;
	gen->frame = 50;
	gen->fl.fi = -40;
	gen->fl.teta = -45;
	gen->shape = 1;
	gen->zoom = 30;
}

// void	find_min_max(t_mlx	*gen)
// {
// 	gen->fl.xmax = gen->fl.x[0][0];
// 	gen->fl.xmin = gen->fl.x[0][0];
// 	gen->fl.ymax = gen->fl.y[0][0];
// 	gen->fl.ymin = gen->fl.y[0][0];
// 	gen->y = 0;
// 	while (gen->y < gen->map_h)
// 	{
// 		gen->x = 0;
// 		while (gen->x < gen->map_w)
// 		{
// 			if (gen->fl.x[gen->y][gen->x] > gen->fl.xmax)
// 				gen->fl.xmax = gen->fl.x[gen->y][gen->x];
// 			if (gen->fl.x[gen->y][gen->x] < gen->fl.xmin)
// 				gen->fl.xmin = gen->fl.x[gen->y][gen->x];
// 			if (gen->fl.y[gen->y][gen->x] > gen->fl.ymax)
// 				gen->fl.ymax = gen->fl.y[gen->y][gen->x];
// 			if (gen->fl.y[gen->y][gen->x] < gen->fl.ymin)
// 				gen->fl.ymin = gen->fl.y[gen->y][gen->x];
// 			gen->x++;
// 		}
// 		gen->y++;
// 	}
// }

void	my_mlx_pixel_put(t_img *gen, int x, int y, unsigned int color)
{
	char	*dst;

	dst = gen->addr + (y * gen->line_len + x * (gen->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

void	init_white_back(t_mlx	*gen)
{
	gen->pic.img = mlx_new_image(gen->mlx, gen->win_w
			+ 2 * gen->frame, gen->win_h + 2 * gen->frame);
	gen->pic.addr = mlx_get_data_addr(gen->pic.img,
			&gen->pic.bits_per_pix, &gen->pic.line_len, &gen->pic.end);
	gen->x = 0;
	while (gen->x < gen->win_h + 2 * gen->frame)
	{
		gen->y = 0;
		while (gen->y < gen->win_w + 2 * gen->frame)
		{
			my_mlx_pixel_put(&gen->pic, gen->y, gen->x, 0x00FFFFFF);
			gen->y++;
		}
		gen->x++;
	}
}

void	swap_xy(t_mlx	*gen)
{
	gen->ln.flag = 0;
	if ((gen->ln.x1 - gen->ln.x0) * (1 - 2 * (gen->ln.x1 < gen->ln.x0))
		< (gen->ln.y1 - gen->ln.y0) * (1 - 2 * (gen->ln.y1 < gen->ln.y0)))
	{
		gen->ln.buf = gen->ln.x0;
		gen->ln.x0 = gen->ln.y0;
		gen->ln.y0 = gen->ln.buf;
		gen->ln.buf = gen->ln.x1;
		gen->ln.x1 = gen->ln.y1;
		gen->ln.y1 = gen->ln.buf;
		gen->ln.flag = 1;
	}
	if (gen->ln.x0 > gen->ln.x1)
	{
		gen->ln.buf = gen->ln.x0;
		gen->ln.x0 = gen->ln.x1;
		gen->ln.x1 = gen->ln.buf;
		gen->ln.buf = gen->ln.y0;
		gen->ln.y0 = gen->ln.y1;
		gen->ln.y1 = gen->ln.buf;
	}
	gen->ln.sgn = 1;
	if (gen->ln.y1 < gen->ln.y0)
		gen->ln.sgn = -1;
}

int	put_pixels_wu(t_mlx	*gen)
{
	if (!gen->ln.flag)
	{
		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_w
			|| gen->ln.ycur < gen->frame
			|| gen->ln.ycur > gen->frame + gen->win_h)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur,
			0x00010101 * (int)(255 * gen->ln.err / gen->ln.dx));
		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur + gen->ln.sgn,
			0x00010101 * (int)(255 * (gen->ln.dx - gen->ln.err) / gen->ln.dx));
	}
	else
	{
		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_h
			|| gen->ln.ycur < gen->frame
			|| gen->ln.ycur > gen->frame + gen->win_w)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.ycur, gen->ln.x,
			0x00010101 * (int)(255 * gen->ln.err / gen->ln.dx));
		my_mlx_pixel_put(&gen->pic, gen->ln.ycur + gen->ln.sgn, gen->ln.x,
			0x00010101 * (int)(255 * (gen->ln.dx - gen->ln.err) / gen->ln.dx));
	}
	return (0);
}

int	put_pixels_bres(t_mlx	*gen)
{
	if (!gen->ln.flag)
	{
		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_w
			|| gen->ln.ycur < gen->frame
			|| gen->ln.ycur > gen->frame + gen->win_h)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur, 0x00000000);
	}
	else
	{
		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_h
			|| gen->ln.ycur < gen->frame
			|| gen->ln.ycur > gen->frame + gen->win_w)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.ycur, gen->ln.x, 0x00000000);
	}
	return (0);
}

int	put_line(t_mlx	*gen)
{
	swap_xy(gen);
	gen->ln.dx = gen->ln.x1 - gen->ln.x0;
	gen->ln.dy = gen->ln.y1 - gen->ln.y0;
	gen->ln.ycur = gen->ln.y0;
	gen->ln.x = gen->ln.x0;
	while (gen->ln.x < gen->ln.x1)
	{
		gen->ln.y = gen->ln.dy * (gen->ln.x - gen->ln.x0)
			+ gen->ln.dx * gen->ln.y0;
		gen->ln.err = gen->ln.sgn * (gen->ln.y - gen->ln.ycur * gen->ln.dx);
		if (gen->ln.err > gen->ln.dx)
		{
			gen->ln.ycur = gen->ln.ycur + gen->ln.sgn;
			gen->ln.err = gen->ln.sgn * (gen->ln.y - gen->ln.ycur * gen->ln.dx);
		}
		put_pixels_wu(gen);
		gen->ln.x++;
	}
	return (0);
}

void	put_pic(t_mlx	*gen)
{
	init_white_back(gen);
	gen->y = 0;
	while (gen->y < gen->map_h)
	{
		gen->x = 0;
		while (gen->x < gen->map_w - 1)
		{
			gen->ln.x0 = gen->fl.x[gen->y][gen->x];
			gen->ln.x1 = gen->fl.x[gen->y][gen->x + 1];
			gen->ln.y0 = gen->fl.y[gen->y][gen->x];
			gen->ln.y1 = gen->fl.y[gen->y][gen->x + 1];
			put_line(gen);
			gen->x++;
		}
		gen->y++;
	}
	gen->x = 0;
	while (gen->x < gen->map_w)
	{
		gen->y = 0;
		while (gen->y < gen->map_h - 1)
		{
			gen->ln.x0 = gen->fl.x[gen->y][gen->x];
			gen->ln.x1 = gen->fl.x[gen->y + 1][gen->x];
			gen->ln.y0 = gen->fl.y[gen->y][gen->x];
			gen->ln.y1 = gen->fl.y[gen->y + 1][gen->x];
			put_line(gen);
			gen->y++;
		}
		gen->x++;
	}
	gen->x = gen->frame;
	while (gen->x < gen->win_w + gen->frame)
	{
		my_mlx_pixel_put(&gen->pic, gen->x, gen->frame, 0x00000000);
		my_mlx_pixel_put(&gen->pic, gen->x, gen->win_h
			+ gen->frame, 0x00000000);
		gen->x++;
	}
	gen->y = gen->frame;
	while (gen->y <= gen->win_h + gen->frame)
	{
		my_mlx_pixel_put(&gen->pic, gen->frame, gen->y, 0x00000000);
		my_mlx_pixel_put(&gen->pic, gen->win_w
			+ gen->frame, gen->y, 0x00000000);
		gen->y++;
	}
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->pic.img);
}

// void	printf_map(t_mlx	*gen)
// {
// 	int	h;
// 	int	w;

// 	h = 0;
// 	w = 0;
// 	while (h < gen->map_h)
// 	{
// 		w = 0;
// 		while (w < gen->map_w)
// 		{
// 			printf("%.1f ", gen->map[h][w]);
// 			w++;
// 		}
// 		printf("\n");
// 		h++;
// 	}
// }

int	get_map_size(t_mlx *gen)
{
	char	*buf;
	char	*ptr;
	int		flag;

	gen->map_fd = open(gen->map_name, O_RDONLY);
	if (gen->map_fd < 0)
	{
		perror("Map error");
		return (1);
	}
	flag = 0;
	gen->map_h = 0;
	gen->map_w = 0;
	buf = get_next_line(gen->map_fd);
	while (buf)
	{
		if (flag == 0)
		{
			ptr = buf;
			while (*buf)
			{
				if (ft_isdigit(*buf) && (*(buf + 1) == ' '
						|| !(*(buf + 1)) || *(buf + 1) == '\n'))
					gen->map_w++;
				buf++;
			}
			buf = ptr;
			flag = 1;
		}
		gen->map_h++;
		free(buf);
		buf = get_next_line(gen->map_fd);
	}
	close(gen->map_fd);
	return (0);
}

int	parse_map(t_mlx *gen)
{
	char	*str;
	char	**spl;

	if (get_map_size(gen))
		return (1);
	gen->map_fd = open(gen->map_name, O_RDONLY);
	gen->map = malloc(sizeof(*gen->map) * gen->map_h);
	if (!gen->map)
		return (1);
	str = get_next_line(gen->map_fd);
	gen->x = 0;
	while (str)
	{
		spl = ft_split(str, ' ');
		free(str);
		gen->map[gen->x] = malloc(sizeof(**gen->map) * gen->map_w);
		if (!gen->map[gen->x])
			return (1);
		gen->y = 0;
		while (spl[gen->y])
		{
			gen->map[gen->x][gen->y] = ft_atoi(spl[gen->y]);
			if (gen->x == 0 && gen->y == 0)
			{
				gen->map_min = gen->map[gen->x][gen->y];
				gen->map_max = gen->map[gen->x][gen->y];
			}
			else if (gen->map[gen->x][gen->y] < gen->map_min)
				gen->map_min = gen->map[gen->x][gen->y];
			else if (gen->map[gen->x][gen->y] > gen->map_max)
				gen->map_max = gen->map[gen->x][gen->y];
			free(spl[gen->y]);
			gen->y++;
		}
		free(spl);
		gen->x++;
		str = get_next_line(gen->map_fd);
	}
	close(gen->map_fd);
	gen->xoffs = (float)(gen->map_h - 1) / 2;
	gen->yoffs = (float)(gen->map_w - 1) / 2;
	return (0);
}

void	malloc_xy(t_mlx	*gen)
{
	gen->fl.x = malloc(sizeof(*gen->fl.x) * gen->map_h);
	gen->fl.y = malloc(sizeof(*gen->fl.y) * gen->map_h);
	gen->y = 0;
	while (gen->y < gen->map_h)
	{
		gen->fl.x[gen->y] = malloc(sizeof(**gen->fl.x) * gen->map_w);
		gen->fl.y[gen->y] = malloc(sizeof(**gen->fl.y) * gen->map_w);
		gen->y++;
	}
}

void	flatten(t_mlx	*gen)
{
	float	cfi;
	float	sfi;
	float	cteta;
	float	steta;

	cfi = cos(M_PI / 180 * gen->fl.fi);
	sfi = sin(M_PI / 180 * gen->fl.fi);
	cteta = cos(M_PI / 180 * gen->fl.teta);
	steta = sin(M_PI / 180 * gen->fl.teta);
	gen->x = 0;
	while (gen->x < gen->map_h)
	{
		gen->y = 0;
		while (gen->y < gen->map_w)
		{
			gen->fl.x[gen->x][gen->y]
				= (cfi * ((float)gen->x - gen->xoffs)
				+ sfi * ((float)gen->y - gen->yoffs)) * gen->zoom
				+ (float)(gen->win_h + 2 * gen->frame) / 2;
			gen->fl.y[gen->x][gen->y]
				= (-sfi * cteta * ((float)gen->x - gen->xoffs)
				+ cfi * cteta * ((float)gen->y - gen->yoffs)
				+ steta * gen->shape * gen->map[gen->x][gen->y]) * gen->zoom
				+ (float)(gen->win_w + 2 * gen->frame) / 2;
			gen->y++;
		}
		gen->x++;
	}
}

void	free_data(t_mlx	*gen)
{
	int	h;

	h = 0;
	while (h < gen->map_h)
	{
		free(gen->map[h]);
		free(gen->fl.x[h]);
		free(gen->fl.y[h]);
		h++;
	}
	free(gen->map);
	free(gen->fl.x);
	free(gen->fl.y);
}

int	rotate(t_mlx *gen)
{
	flatten(gen);
	put_pic(gen);
	gen->fl.fi = gen->fl.fi - 0.3;
	if (gen->fl.fi < -360)
		gen->fl.fi = gen->fl.fi + 360;
	usleep(16666);
	return (0);
}

int	close_win(int keycode, t_mlx	*gen)
{
	if (keycode == 0)
		mlx_destroy_window(gen->mlx, gen->win);
	return (0);
}

int	main(void)
{
	t_mlx	gen;

	def_vars(&gen);
	if (parse_map(&gen))
		return (1);
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, gen.win_w + 2 * gen.frame,
			gen.win_h + 2 * gen.frame, "Fdf");
	malloc_xy(&gen);
	mlx_loop_hook(gen.mlx, rotate, &gen);
	// rotate(&gen);
	// mlx_key_hook(gen.mlx, close_win, &gen);
	mlx_loop(gen.mlx);
	free_data(&gen);
	return (0);
}
