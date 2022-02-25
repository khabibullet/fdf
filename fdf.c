/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/25 12:54:41 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_lib.h"

void	print_ptr_array(float	**arr, int h, int w)
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
			printf("%.1f%c", arr[y][x], c);
			x++;
		}
		y++;
	}
}

void	print_3x3_array(float arr[3][3])
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < 3)
	{
		x = 0;
		c = ' ';
		while (x < 3)
		{
			if (x == 2)
				c = '\n';
			printf("%.1f%c", arr[y][x], c);
			x++;
		}
		y++;
	}
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

// void	my_mlx_pixel_put(t_img *gen, int x, int y, unsigned int color)
// {
// 	char	*dst;

// 	dst = gen->addr + (y * gen->line_len + x * (gen->bits_per_pix / 8));
// 	*(unsigned int *)dst = color;
// }

// void	put_white_back(t_mlx	*gen)
// {
// 	gen->pic.img = mlx_new_image(gen->mlx, gen->win_w
// 			+ 2 * gen->frame, gen->win_h + 2 * gen->frame);
// 	gen->pic.addr = mlx_get_data_addr(gen->pic.img,
// 			&gen->pic.bits_per_pix, &gen->pic.line_len, &gen->pic.end);
// 	gen->x = 0;
// 	while (gen->x < gen->win_h + 2 * gen->frame)
// 	{
// 		gen->y = 0;
// 		while (gen->y < gen->win_w + 2 * gen->frame)
// 		{
// 			my_mlx_pixel_put(&gen->pic, gen->y, gen->x, 0x00FFFFFF);
// 			gen->y++;
// 		}
// 		gen->x++;
// 	}
// }

// void	swap_xy(t_mlx	*gen)
// {
// 	gen->ln.flag = 0;
// 	if ((gen->ln.x1 - gen->ln.x0) * (1 - 2 * (gen->ln.x1 < gen->ln.x0))
// 		< (gen->ln.y1 - gen->ln.y0) * (1 - 2 * (gen->ln.y1 < gen->ln.y0)))
// 	{
// 		gen->ln.buf = gen->ln.x0;
// 		gen->ln.x0 = gen->ln.y0;
// 		gen->ln.y0 = gen->ln.buf;
// 		gen->ln.buf = gen->ln.x1;
// 		gen->ln.x1 = gen->ln.y1;
// 		gen->ln.y1 = gen->ln.buf;
// 		gen->ln.flag = 1;
// 	}
// 	if (gen->ln.x0 > gen->ln.x1)
// 	{
// 		gen->ln.buf = gen->ln.x0;
// 		gen->ln.x0 = gen->ln.x1;
// 		gen->ln.x1 = gen->ln.buf;
// 		gen->ln.buf = gen->ln.y0;
// 		gen->ln.y0 = gen->ln.y1;
// 		gen->ln.y1 = gen->ln.buf;
// 	}
// 	gen->ln.sgn = 1;
// 	if (gen->ln.y1 < gen->ln.y0)
// 		gen->ln.sgn = -1;
// }

// int	put_pixels_wu(t_mlx	*gen)
// {
// 	if (!gen->ln.flag)
// 	{
// 		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_h
// 			|| gen->ln.ycur < gen->frame
// 			|| gen->ln.ycur > gen->frame + gen->win_w)
// 			return (1);
// 		my_mlx_pixel_put(&gen->pic, gen->ln.ycur, gen->ln.x,
// 			0x00010101 * (int)(255 * gen->ln.err / gen->ln.dx));
// 		my_mlx_pixel_put(&gen->pic, gen->ln.ycur + gen->ln.sgn, gen->ln.x,
// 			0x00010101 * (int)(255 * (gen->ln.dx - gen->ln.err) / gen->ln.dx));
// 	}
// 	else
// 	{
// 		if (gen->ln.x < gen->frame || gen->ln.x > gen->frame + gen->win_w
// 			|| gen->ln.ycur < gen->frame
// 			|| gen->ln.ycur > gen->frame + gen->win_h)
// 			return (1);
// 		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur,
// 			0x00010101 * (int)(255 * gen->ln.err / gen->ln.dx));
// 		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur + gen->ln.sgn,
// 			0x00010101 * (int)(255 * (gen->ln.dx - gen->ln.err) / gen->ln.dx));
// 	}
// 	return (0);
// }

// int	put_pixels_bres(t_mlx	*gen)
// {
// 	if (!gen->ln.flag)
// 	{
// 		if (gen->ln.x <= gen->frame || gen->ln.x >= gen->frame + gen->win_h
// 			|| gen->ln.ycur <= gen->frame
// 			|| gen->ln.ycur >= gen->frame + gen->win_w)
// 			return (1);
// 		my_mlx_pixel_put(&gen->pic, gen->ln.ycur, gen->ln.x, 0x00000000);
// 	}
// 	else
// 	{
// 		if (gen->ln.x <= gen->frame || gen->ln.x >= gen->frame + gen->win_w
// 			|| gen->ln.ycur <= gen->frame
// 			|| gen->ln.ycur >= gen->frame + gen->win_h)
// 			return (1);
// 		my_mlx_pixel_put(&gen->pic, gen->ln.x, gen->ln.ycur, 0x00000000);
// 	}
// 	return (0);
// }

// int	put_line(t_mlx	*gen)
// {
// 	swap_xy(gen);
// 	gen->ln.dx = gen->ln.x1 - gen->ln.x0;
// 	gen->ln.dy = gen->ln.y1 - gen->ln.y0;
// 	gen->ln.ycur = gen->ln.y0;
// 	gen->ln.x = gen->ln.x0;
// 	while (gen->ln.x < gen->ln.x1)
// 	{
// 		gen->ln.y = gen->ln.dy * (gen->ln.x - gen->ln.x0)
// 			+ gen->ln.dx * gen->ln.y0;
// 		gen->ln.err = gen->ln.sgn * (gen->ln.y - gen->ln.ycur * gen->ln.dx);
// 		if (gen->ln.err > gen->ln.dx)
// 		{
// 			gen->ln.ycur = gen->ln.ycur + gen->ln.sgn;
// 			gen->ln.err = gen->ln.sgn * (gen->ln.y - gen->ln.ycur * gen->ln.dx);
// 		}
// 		put_pixels_wu(gen);
// 		gen->ln.x++;
// 	}
// 	return (0);
// }

// void	put_frame(t_mlx	*gen)
// {
// 	gen->x = gen->frame;
// 	while (gen->x < gen->win_w + gen->frame)
// 	{
// 		my_mlx_pixel_put(&gen->pic, gen->x, gen->frame, 0x00000000);
// 		my_mlx_pixel_put(&gen->pic, gen->x, gen->win_h
// 			+ gen->frame, 0x00000000);
// 		gen->x++;
// 	}
// 	gen->y = gen->frame;
// 	while (gen->y <= gen->win_h + gen->frame)
// 	{
// 		my_mlx_pixel_put(&gen->pic, gen->frame, gen->y, 0x00000000);
// 		my_mlx_pixel_put(&gen->pic, gen->win_w
// 			+ gen->frame, gen->y, 0x00000000);
// 		gen->y++;
// 	}
// 	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
// 	mlx_destroy_image(gen->mlx, gen->pic.img);
// }

// void	set_and_draw(t_mlx	*gen, int flag)
// {
// 	if (flag == 1 || flag == 3)
// 	{
// 		gen->ln.x0 = gen->fl.x[gen->x][gen->y];
// 		gen->ln.x1 = gen->fl.x[gen->x][gen->y + 1];
// 		gen->ln.y0 = gen->fl.y[gen->x][gen->y];
// 		gen->ln.y1 = gen->fl.y[gen->x][gen->y + 1];
// 		put_line(gen);
// 		if (flag == 1)
// 			gen->y++;
// 		else
// 			gen->y--;
// 	}
// 	else if (flag == 2 || flag == 4)
// 	{
// 		gen->ln.x0 = gen->fl.x[gen->y][gen->x];
// 		gen->ln.x1 = gen->fl.x[gen->y + 1][gen->x];
// 		gen->ln.y0 = gen->fl.y[gen->y][gen->x];
// 		gen->ln.y1 = gen->fl.y[gen->y + 1][gen->x];
// 		put_line(gen);
// 		if (flag == 2)
// 			gen->y++;
// 		else
// 			gen->y--;
// 	}
// }

// void	put_case_1(t_mlx	*gen)
// {
// 	gen->x = 0;
// 	while (gen->x < gen->map_h)
// 	{
// 		gen->y = 0;
// 		while (gen->y < gen->map_w - 1)
// 			set_and_draw(gen, 1);
// 		gen->x++;
// 	}
// 	gen->x = 0;
// 	while (gen->x < gen->map_w)
// 	{
// 		gen->y = 0;
// 		while (gen->y < gen->map_h - 1)
// 			set_and_draw(gen, 2);
// 		gen->x++;
// 	}
// }

// void	put_case_2(t_mlx	*gen)
// {
// 	gen->x = gen->map_h - 1;
// 	while (gen->x >= 0)
// 	{
// 		gen->y = gen->map_w - 2;
// 		while (gen->y >= 0)
// 			set_and_draw(gen, 3);
// 		gen->x--;
// 	}
// 	gen->x = gen->map_w - 1;
// 	while (gen->x >= 0)
// 	{
// 		gen->y = gen->map_h - 2;
// 		while (gen->y >= 0)
// 			set_and_draw(gen, 4);
// 		gen->x--;
// 	}
// }

// void	put_pic(t_mlx	*gen)
// {
// 	put_white_back(gen);
// 	if (gen->fl.fi > 90 && gen->fl.fi < 270)
// 		put_case_1(gen);
// 	else
// 		put_case_2(gen);
// 	put_frame(gen);
// }

// void	flatten(t_mlx	*gen)
// {
// 	t_angles	ang;

// 	ang.cfi = cos(M_PI / 180 * gen->fl.fi);
// 	ang.sfi = sin(M_PI / 180 * gen->fl.fi);
// 	ang.cteta = cos(M_PI / 180 * gen->fl.teta);
// 	ang.steta = sin(M_PI / 180 * gen->fl.teta);
// 	gen->x = 0;
// 	while (gen->x < gen->map_h)
// 	{
// 		gen->y = 0;
// 		while (gen->y < gen->map_w)
// 		{
// 			gen->fl.y[gen->x][gen->y] = (ang.cfi * ((float)gen->x
// 						- gen->xoffs) + ang.sfi * ((float)gen->y - gen->yoffs))
// 				* gen->zoom + (float)(gen->win_w + 2 * gen->frame) / 2;
// 			gen->fl.x[gen->x][gen->y] = (ang.sfi * ang.cteta * ((float)gen->x
// 						- gen->xoffs) - ang.cfi * ang.cteta * ((float)gen->y
// 						- gen->yoffs) - ang.steta * gen->shape
// 					* gen->map[gen->x][gen->y]) * gen->zoom
// 				+ (float)(gen->win_h + 2 * gen->frame) / 2;
// 			gen->y++;
// 		}
// 		gen->x++;
// 	}
// }

// void	free_data(t_mlx	*gen)
// {
// 	int	h;

// 	h = 0;
// 	while (h < gen->map_h)
// 	{
// 		free(gen->map[h]);
// 		free(gen->fl.x[h]);
// 		free(gen->fl.y[h]);
// 		h++;
// 	}
// 	free(gen->map);
// 	free(gen->fl.x);
// 	free(gen->fl.y);
// }

// int	close_win(int keycode, t_mlx	*gen)
// {
// 	if (keycode == 53)
// 	{
// 		mlx_destroy_window(gen->mlx, gen->win);
// 		exit(0);
// 	}
// 	return (0);
// }

// int	interact(t_mlx *gen)
// {
// 	// mlx_loop_hook(gen.mlx, rotate, &gen);
// 	// mlx_hook(gen.win, 6, 0, mouse_move, &gen);
// 	// mlx_hook(gen.win, 2, 0, rot_off, &gen);
// 	// mlx_hook(gen->win, 4, 0, mouse_press, gen);
// 	mlx_hook(gen->win, 17, 0, close_win, gen);
// 	return (0);
// }

// void	limit_and_center(t_mlx *gen)
// {
// 	find_min_max(gen);
// 	gen->zoom = 0.8 * gen->win_w / (gen->fl.ymax - gen->fl.ymin);
// 	if (gen->fl.xmax - gen->fl.xmin > 0.8 * gen->win_h)
// 		gen->zoom = 0.8 * gen->win_h / (gen->fl.xmax - gen->fl.xmin);
// 	gen->x = 0;
// 	while (gen->x < gen->win_h)
// 	{
// 		gen->y = 0;
// 		while (gen->y < gen->win_w)
// 		{
// 			gen->fl.x[gen->x][gen->y] += 1;
// 				// (gen->frame + gen->win_h
// 					// - gen->fl.xmax - gen->fl.xmin) / 2;
// 			gen->y++;
// 		}
// 		gen->x++;
// 	}
// }

// int	rotate(t_mlx *gen)
// {
// 	flatten(gen);
// 	put_pic(gen);
// 	gen->fl.fi = gen->fl.fi + 0.3;
// 	if (gen->fl.fi > 360)
// 		gen->fl.fi = gen->fl.fi - 360;
// 	if (gen->fl.teta > 90)
// 		gen->fl.teta = 90;
// 	if (gen->fl.teta < 0)
// 		gen->fl.teta = 0;
// 	usleep(8333);
// 	return (0);
// }

// int mouse_move(int x, int y, t_mlx *gen)
// {
// 	(void)gen;
// 	printf("%d - %d\n", x, y);
// 	return (0);
// }

// int	default_draw(t_mlx *gen)
// {
// 	flatten(gen);
// 	limit_and_center(gen);
// 	put_pic(gen);
// 	return (0);
// }

void	get_rot_matrix(float rot[3][3], float *angles)
{
	float	fi;
	float	teta;

	fi = -angles[0] / 180 * M_PI;
	teta = -angles[1] / 180 * M_PI;

	rot[0][2] = 0;
	rot[0][0] = cos(fi);
	rot[0][1] = sin(fi);
	rot[1][2] = sin(teta);
	rot[2][2] = cos(teta);
	rot[1][0] = -rot[0][1] * rot[2][2];
	rot[1][1] = rot[0][0] * rot[2][2];
	rot[2][0] = rot[0][1] * rot[1][2];
	rot[2][1] = -rot[1][2] * rot[0][0];

	angles[0] = -fi * 180 / M_PI;
	angles[1] = -teta * 180 / M_PI;
}

// void	move_cam(float ****v1, float ****v2, int *shift, float rot[3][3])
// {
// 	int	h;
// 	int	w;

// 	while (h < )
// }


int	main(void)
{
	t_mlx	gen;

	get_parsed(&gen.v1, &gen.v2, gen.msize, "maps/plat.fdf");
	gen.angles[0] = 45;
	gen.angles[1] = 45;
	get_rot_matrix(gen.rot, gen.angles);
	print_3x3_array(gen.rot);
	// move_cam(&gen.v1, &genv1, gen.shift, gen.rot);
	// print_ptr_array(gen.v1[2], gen.msize[0], gen.msize[1]);
	// gen.mlx = mlx_init(); 
	// gen.win = mlx_new_window(gen.mlx, gen.win_w + 2 * gen.frame,
	// 		gen.win_h + 2 * gen.frame, "Fdf");
	// default_draw(&gen);
	// mlx_loop(gen.mlx);
	// free_data(&gen);
	exit (EXIT_SUCCESS);
}
