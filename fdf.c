/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/24 01:52:43 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_lib.h"
// #include "src/ft_printf.c"
// #include "src/ft_atoi.c"
// #include "src/ft_isdigit.c"
// #include "src/ft_putchar.c"
// #include "src/ft_puthex.c"
// #include "src/ft_putnbr.c"
// #include "src/ft_atoi.c"
// #include "src/ft_atoi.c"
// #include "src/ft_atoi.c"
// #include "src/ft_atoi.c"
// #include "src/ft_atoi.c"
// #include "src/ft_atoi.c"

void	def_vars(t_mlx	*gen)
{
	gen->map_name = "maps/plat.fdf";
	gen->wsize[0] = 500; //height
	gen->wsize[1] = 500; //width
	gen->frame = 50;
	gen->fl.fi = 2;
	gen->fl.teta = 60;
	gen->shape = 1;
	gen->zoom = 15;
}

void	find_min_max(t_mlx	*gen)
{
	gen->fl.xmax = gen->fl.x[0][0];
	gen->fl.xmin = gen->fl.x[0][0];
	gen->fl.ymax = gen->fl.y[0][0];
	gen->fl.ymin = gen->fl.y[0][0];
	gen->y = 0;
	while (gen->y < gen->map_h)
	{
		gen->x = 0;
		while (gen->x < gen->map_w)
		{
			if (gen->fl.x[gen->y][gen->x] > gen->fl.xmax)
				gen->fl.xmax = gen->fl.x[gen->y][gen->x];
			if (gen->fl.x[gen->y][gen->x] < gen->fl.xmin)
				gen->fl.xmin = gen->fl.x[gen->y][gen->x];
			if (gen->fl.y[gen->y][gen->x] > gen->fl.ymax)
				gen->fl.ymax = gen->fl.y[gen->y][gen->x];
			if (gen->fl.y[gen->y][gen->x] < gen->fl.ymin)
				gen->fl.ymin = gen->fl.y[gen->y][gen->x];
			gen->x++;
		}
		gen->y++;
	}
}

void	my_mlx_pixel_put(t_img *gen, int x, int y, unsigned int color)
{
	char	*dst;

	dst = gen->addr + (y * gen->line_len + x * (gen->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

void	put_white_back(t_mlx	*gen)
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
		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_h
			|| gen->ln.ycur < gen->frame
			|| gen->ln.ycur > gen->frame + gen->win_w)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.ycur, gen->ln.x,
			0x00010101 * (int)(255 * gen->ln.err / gen->ln.dx));
		my_mlx_pixel_put(&gen->pic, gen->ln.ycur + gen->ln.sgn, gen->ln.x,
			0x00010101 * (int)(255 * (gen->ln.dx - gen->ln.err) / gen->ln.dx));
	}
	else
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
	return (0);
}

int	put_pixels_bres(t_mlx	*gen)
{
	if (!gen->ln.flag)
	{
		if (gen->ln.x <= gen->frame || gen->ln.x >= gen->frame + gen->win_h
			|| gen->ln.ycur <= gen->frame
			|| gen->ln.ycur >= gen->frame + gen->win_w)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.ycur, gen->ln.x, 0x00000000);
	}
	else
	{
		if (gen->ln.x <= gen->frame || gen->ln.x >= gen->frame + gen->win_w
			|| gen->ln.ycur <= gen->frame
			|| gen->ln.ycur >= gen->frame + gen->win_h)
			return (1);
		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur, 0x00000000);
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

void	put_frame(t_mlx	*gen)
{
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

void	set_and_draw(t_mlx	*gen, int flag)
{
	if (flag == 1 || flag == 3)
	{
		gen->ln.x0 = gen->fl.x[gen->x][gen->y];
		gen->ln.x1 = gen->fl.x[gen->x][gen->y + 1];
		gen->ln.y0 = gen->fl.y[gen->x][gen->y];
		gen->ln.y1 = gen->fl.y[gen->x][gen->y + 1];
		put_line(gen);
		if (flag == 1)
			gen->y++;
		else
			gen->y--;
	}
	else if (flag == 2 || flag == 4)
	{
		gen->ln.x0 = gen->fl.x[gen->y][gen->x];
		gen->ln.x1 = gen->fl.x[gen->y + 1][gen->x];
		gen->ln.y0 = gen->fl.y[gen->y][gen->x];
		gen->ln.y1 = gen->fl.y[gen->y + 1][gen->x];
		put_line(gen);
		if (flag == 2)
			gen->y++;
		else
			gen->y--;
	}
}

void	put_case_1(t_mlx	*gen)
{
	gen->x = 0;
	while (gen->x < gen->map_h)
	{
		gen->y = 0;
		while (gen->y < gen->map_w - 1)
			set_and_draw(gen, 1);
		gen->x++;
	}
	gen->x = 0;
	while (gen->x < gen->map_w)
	{
		gen->y = 0;
		while (gen->y < gen->map_h - 1)
			set_and_draw(gen, 2);
		gen->x++;
	}
}

void	put_case_2(t_mlx	*gen)
{
	gen->x = gen->map_h - 1;
	while (gen->x >= 0)
	{
		gen->y = gen->map_w - 2;
		while (gen->y >= 0)
			set_and_draw(gen, 3);
		gen->x--;
	}
	gen->x = gen->map_w - 1;
	while (gen->x >= 0)
	{
		gen->y = gen->map_h - 2;
		while (gen->y >= 0)
			set_and_draw(gen, 4);
		gen->x--;
	}
}

void	put_pic(t_mlx	*gen)
{
	put_white_back(gen);
	if (gen->fl.fi > 90 && gen->fl.fi < 270)
		put_case_1(gen);
	else
		put_case_2(gen);
	put_frame(gen);
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

void	print_array(float	**arr, int h, int w)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < h)
	{
		x = 0;
		c = ' ';
		while (x < w)
		{
			if (x == w - 1)
				c = '\n';
			ft_printf("%d%c", (int)arr[y][x], c);
			x++;
		}
		y++;
	}
}

void	flatten(t_mlx	*gen)
{
	t_angles	ang;

	ang.cfi = cos(M_PI / 180 * gen->fl.fi);
	ang.sfi = sin(M_PI / 180 * gen->fl.fi);
	ang.cteta = cos(M_PI / 180 * gen->fl.teta);
	ang.steta = sin(M_PI / 180 * gen->fl.teta);
	gen->x = 0;
	while (gen->x < gen->map_h)
	{
		gen->y = 0;
		while (gen->y < gen->map_w)
		{
			gen->fl.y[gen->x][gen->y] = (ang.cfi * ((float)gen->x
						- gen->xoffs) + ang.sfi * ((float)gen->y - gen->yoffs))
				* gen->zoom + (float)(gen->win_w + 2 * gen->frame) / 2;
			gen->fl.x[gen->x][gen->y] = (ang.sfi * ang.cteta * ((float)gen->x
						- gen->xoffs) - ang.cfi * ang.cteta * ((float)gen->y
						- gen->yoffs) - ang.steta * gen->shape
					* gen->map[gen->x][gen->y]) * gen->zoom
				+ (float)(gen->win_h + 2 * gen->frame) / 2;
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

int	close_win(int keycode, t_mlx	*gen)
{
	if (keycode == 53)
	{
		mlx_destroy_window(gen->mlx, gen->win);
		exit(0);
	}
	return (0);
}

int	interact(t_mlx *gen)
{
	// mlx_loop_hook(gen.mlx, rotate, &gen);
	// mlx_hook(gen.win, 6, 0, mouse_move, &gen);
	// mlx_hook(gen.win, 2, 0, rot_off, &gen);
	// mlx_hook(gen->win, 4, 0, mouse_press, gen);
	mlx_hook(gen->win, 17, 0, close_win, gen);
	return (0);
}

void	limit_and_center(t_mlx *gen)
{
	find_min_max(gen);
	gen->zoom = 0.8 * gen->win_w / (gen->fl.ymax - gen->fl.ymin);
	if (gen->fl.xmax - gen->fl.xmin > 0.8 * gen->win_h)
		gen->zoom = 0.8 * gen->win_h / (gen->fl.xmax - gen->fl.xmin);
	gen->x = 0;
	while (gen->x < gen->win_h)
	{
		gen->y = 0;
		while (gen->y < gen->win_w)
		{
			gen->fl.x[gen->x][gen->y] += 1;
				// (gen->frame + gen->win_h
					// - gen->fl.xmax - gen->fl.xmin) / 2;
			gen->y++;
		}
		gen->x++;
	}
}

int	rotate(t_mlx *gen)
{
	flatten(gen);
	put_pic(gen);
	gen->fl.fi = gen->fl.fi + 0.3;
	if (gen->fl.fi > 360)
		gen->fl.fi = gen->fl.fi - 360;
	if (gen->fl.teta > 90)
		gen->fl.teta = 90;
	if (gen->fl.teta < 0)
		gen->fl.teta = 0;
	usleep(8333);
	return (0);
}

int mouse_move(int x, int y, t_mlx *gen)
{
	(void)gen;
	printf("%d - %d\n", x, y);
	return (0);
}

int	default_draw(t_mlx *gen)
{
	flatten(gen);
	limit_and_center(gen);
	put_pic(gen);
	return (0);
}

int	main(void)
{
	t_mlx	gen;

	parse_map(gen.v1, gen.v2, gen.msize, "maps/plat.fdf");
	// print_array(gen.v1[2], gen.msize[0], gen.msize[1]);
	// gen.mlx = mlx_init(); 
	// gen.win = mlx_new_window(gen.mlx, gen.win_w + 2 * gen.frame,
	// 		gen.win_h + 2 * gen.frame, "Fdf");
	// default_draw(&gen);
	// mlx_loop(gen.mlx);
	// free_data(&gen);
	exit (EXIT_SUCCESS);
}
