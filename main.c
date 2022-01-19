/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/01/19 21:59:43 by anemesis         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *gen, int x, int y, unsigned int color)
{
	char	*dst;

	dst = gen->addr + (y * gen->line_len + x * (gen->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

void	init_white_back(t_mlx	*gen)
{
	gen->pic.img = mlx_new_image(gen->mlx, gen->win_w, gen->win_h);
	gen->pic.addr = mlx_get_data_addr(gen->pic.img,
			&gen->pic.bits_per_pix, &gen->pic.line_len, &gen->pic.end);
	gen->y_pix = 0;
	while (gen->y_pix < gen->win_h)
	{
		gen->x_pix = 0;
		while (gen->x_pix < gen->win_w)
		{
			my_mlx_pixel_put(&gen->pic, gen->x_pix, gen->y_pix, 0x00FFFFFF);
			gen->x_pix++;
		}
		gen->y_pix++;
	}
}

int	abso(int i)
{
	if (i >= 0)
		return (i);
	else
		return (-i);
}

void	bres_line(t_mlx	*gen)
{
	int	buf;
	int	sign;
	int	yprev;
	int	flag;
	int	err1;
	int	err2;
	int	dx;
	int	dy;

	flag = 0;
	if (abso(gen->x1 - gen->x0) < abso(gen->y1 - gen->y0))
	{
		buf = gen->x0;
		gen->x0 = gen->y0;
		gen->y0 = buf;
		buf = gen->x1;
		gen->x1 = gen->y1;
		gen->y1 = buf;
		flag = 1;
	}
	if (gen->x0 > gen->x1)
	{
		buf = gen->x0;
		gen->x0 = gen->x1;
		gen->x1 = buf;
		buf = gen->y0;
		gen->y0 = gen->y1;
		gen->y1 = buf;
	}
	sign = 1;
	yprev = gen->y0;
	if (gen->y1 < gen->y0)
		sign = -1;
	dx = gen->x1 - gen->x0;
	dy = gen->y1 - gen->y0;
	gen->x = gen->x0;
	while (gen->x <= gen->x1)
	{
		gen->y = dy * (gen->x - gen->x0) + gen->y0 * dx;
		err1 = abso(yprev * dx - gen->y);
		err2 = abso((yprev + sign) * dx - gen->y);
		if (err1 > err2)
			yprev = yprev + sign;
		if (!flag)
		{
			my_mlx_pixel_put(&gen->pic, gen->x, yprev,
				0x00010101 * (int)(255 * err1 / (err1 + err2)));
			my_mlx_pixel_put(&gen->pic, gen->x,
				yprev + (1 - 2 * (yprev * dx - gen->y > 0)),
				0x00010101 * (int)(255 * err2 / (err1 + err2)));
		}
		else
		{
			my_mlx_pixel_put(&gen->pic, yprev, gen->x,
				0x00010101 * (int)(255 * err1 / (err1 + err2)));
			my_mlx_pixel_put(&gen->pic,
				yprev + (1 - 2 * (yprev * dx - gen->y > 0)), gen->x,
				0x00010101 * (int)(255 * err2 / (err1 + err2)));
		}
		printf("%d -- %d\n", (int)(255 * err1 / (err1 + err2)), (int)(255 * err2 / (err1 + err2)));
		gen->x++;
	}
}

void	put_pic(t_mlx	*gen)
{
	init_white_back(gen);
	bres_line(gen);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
}

void	printf_map(t_mlx	*gen)
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (h < gen->map_h)
	{
		w = 0;
		while (w < gen->map_w)
		{
			printf("%d ", gen->map[h][w]);
			w++;
		}
		printf("\n");
		h++;
	}
}

void	free_map(t_mlx	*gen)
{
	int	h;

	h = 0;
	while (h < gen->map_h)
	{
		free(*gen->map);
		gen->map++;
		h++;
	}
	gen->map = gen->map - gen->map_h;
	free(gen->map);
}

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
	while (str)
	{
		spl = ft_split(str, ' ');
		free(str);
		*gen->map = malloc(sizeof(**gen->map) * gen->map_w);
		if (!*gen->map)
			return (1);
		while (*spl)
		{
			**gen->map = ft_atoi(*spl);
			free(*spl);
			spl++;
			(*gen->map)++;
		}
		*gen->map = *gen->map - gen->map_w;
		(gen->map)++;
		spl = spl - gen->map_w;
		free(spl);
		str = get_next_line(gen->map_fd);
	}
	gen->map = gen->map - gen->map_h;
	close(gen->map_fd);
	return (0);
}

void	def_vars(t_mlx	*gen)
{
	gen->map_name = "basictest_2.fdf";
	gen->win_h = 500;
	gen->win_w = 500;
	gen->x0 = 400;
	gen->x1 = 50;
	gen->y0 = 200;
	gen->y1 = 210;
}

int	main(void)
{
	t_mlx	gen;

	def_vars(&gen);
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, gen.win_w, gen.win_h, "Fdf");
	put_pic(&gen);
	mlx_loop(gen.mlx);
	return (0);
}
