/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/25 21:53:30 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_lib.h"

void	my_mlx_pixel_put(t_img *pic, int x, int y, unsigned int color)
{
	char	*dst;

	dst = pic->addr + (y * pic->len + x * (pic->depth / 8));
	if (*(unsigned int *)dst == 0x00FFFFFF)
		*(unsigned int *)dst = color;
}

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

void	get_persp_projection(float ***v1, float focal, int *wsize, int *msize)
{
	int		h;
	int		w;
	float	z;

	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			z = v1[2][h][w];
			v1[0][h][w] = (f * v1[0][h][w] / z) + wsize[0] / 2;
			v1[1][h][w] = -(f * v1[1][h][w] / z) + wsize[1] / 2;
			v1[2][h][w] = f;
			w++;
		}
		h++;
	}
}

void	get_isomet_projection(float ***v1, float focal, int *wsize, int *msize)
{
	int		h;
	int		w;
	float	z;

	z = average(v1[2], msize);
	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			v1[0][h][w] = (f * v1[0][h][w] / z) + wsize[0] / 2;
			v1[1][h][w] = -(f * v1[1][h][w] / z) + wsize[1] / 2;
			v1[2][h][w] = f;
			w++;
		}
		h++;
	}
}

void	put_white_back(t_img *pic, void *mlx, int *wsize)
{
	int		x;
	int		y;
	char	*dst;

	pic->img = mlx_new_image(mlx, wsize[1], wsize[0]);
	pic->addr = mlx_get_data_addr(pic->img,
			&pic->depth, &pic->len, &pic->end);
	y = 0;
	while (y < wsize[0])
	{
		x = 0;
		while (x < wsize[1])
		{
			dst = pic->addr + (y * pic->len + x * (pic->depth / 8));
			*(unsigned int *)dst = 0x00FFFFFF;
			x++;
		}
		y++;
	}
}

void	draw_map(t_mlx	*gen)
{
	put_white_back(&gen->pic, gen->mlx, gen->wsize);
	get_persp_projection(gen->v1, gen->focal, gen->wsize, gen->msize);
	get_isomet_projection(gen->v1, gen->focal, gen->wsize, gen->msize);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->pic.img);
}

/*
	** v1 vector is vector to be plotted
	** v2 is vector which stores unrotated coordinates
*/

void	get_defaults(t_mlx	*gen)
{
	gen->angles[0] = 0;
	gen->angles[1] = 0;
	gen->shift[0] = 0;
	gen->shift[1] = 0;
	gen->shift[2] = -15;
	gen->wsize[0] = 500;
	gen->wsize[1] = 700;
	gen->focal = gen->wsize[0] / tan(60 / 180 * M_PI) / 2;
}

int	main(void)
{
	t_mlx	gen;

	get_parsed(&gen.v1, &gen.v2, gen.msize, "maps/plat.fdf");
	get_defaults(&gen);
	move_cam(&gen, gen.shift, gen.angles, gen.msize);
	gen.angles[0] = 45;
	gen.angles[1] = 45;
	rotate_cam(gen.v2, gen.v1, gen.angles, gen.msize);
	print_ptr_array(gen.v1[0], gen.msize[0], gen.msize[1]);
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, gen.wsize[1], gen.wsize[0], "Fdf");
	draw_map(&gen);
	mlx_loop(gen.mlx);
	exit (EXIT_SUCCESS);
}
