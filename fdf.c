/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/02 21:25:23 by anemesis         ###   ########.fr       */
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

void	put_pixels_wu(t_img *pic, t_line ln)
{
	if (!ln.flag)
	{
		my_mlx_pixel_put(pic, ln.x, ln.ycur,
			0x00010101 * (int)(255 * ln.err / ln.dx));
		my_mlx_pixel_put(pic, ln.x, ln.ycur + ln.sgn,
			0x00010101 * (int)(255 * (1 - ln.err / ln.dx)));
	}
	else
	{
		my_mlx_pixel_put(pic, ln.ycur, ln.x,
			0x00010101 * (int)(255 * ln.err / ln.dx));
		my_mlx_pixel_put(pic, ln.ycur, ln.x + ln.sgn,
			0x00010101 * (int)(255 * (1 - ln.err / ln.dx)));
	}
}

void	is_inside(float ***v1, int *msize, int *wsize)
{
	int	h;
	int	w;
	int	flag;

	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			if (v1[0][h][w] < 0 || v1[0][h][w] > wsize[1]
				|| v1[1][h][w] < 0 || v1[1][h][w] > wsize[0])
				flag = 1;
			w++;
		}
		h++;
	}
	if (!flag)
		printf("OKAY\n");
	else
		printf("OUT OF WINDOW\n");
}

void	swap_pairs(float *a1, float *a2, float *b1, float *b2)
{
	float	buf;

	buf = *a1;
	*a1 = *a2;
	*a2 = buf;
	buf = *b1;
	*b1 = *b2;
	*b2 = buf;
}

void	put_line(t_img	*pic, float xx_yy[4])
{
	t_line	ln;

	ln.flag = 0;
	ln.x1 = xx_yy[0];
	ln.x2 = xx_yy[1];
	ln.y1 = xx_yy[2];
	ln.y2 = xx_yy[3];
	ln.dx = ln.x2 - ln.x1;
	ln.dy = ln.y2 - ln.y1;
	if (ln.dy > ln.dx)
	{
		if (ln.dy > 0)
			swap_pairs(&ln.x1, &ln.y1, &ln.x2, &ln.y2);
		else if (ln.dy < 0)
			swap_pairs(&ln.x1, &ln.y2, &ln.x2, &ln.y1);
		ln.flag = 1;
	}
	ln.sgn = 1;
	if (ln.dy < 0)
		ln.sgn = -1;
	ln.ycur = ln.y1;
	ln.x = ln.x1;
	while (ln.x < ln.x2)
	{
		ln.y = ln.dy * (ln.x - ln.x1) + ln.dx * ln.y1;
		ln.err = ln.sgn * (ln.y - ln.ycur * ln.dx);
		if (ln.err > ln.dx)
		{
			ln.ycur = ln.ycur + ln.sgn;
			ln.err = ln.sgn * (ln.y - ln.ycur * ln.dx);
		}
		put_pixels_wu(pic, ln);
		ln.x++;
	}
}

float	crop_x(float xx_yy[4], int *wsize)
{
	float	k;

	if (xx_yy[0] > xx_yy[1])
		swap_pairs(&xx_yy[0], &xx_yy[1], &xx_yy[2], &xx_yy[3]);
	k = (xx_yy[3] - xx_yy[2]) / (xx_yy[1] - xx_yy[0]);
	if (xx_yy[0] < 0)
	{
		xx_yy[2] = xx_yy[2] - (xx_yy[0] * k);
		xx_yy[0] = 0;
	}
	if (xx_yy[1] > (float)wsize[1])
	{
		xx_yy[3] = xx_yy[3] + (wsize[1] - xx_yy[1]) * k;
		xx_yy[1] = wsize[1];
	}
	return (k);
}

void	crop_y(float xx_yy[4], float k, int fl, int *wsize)
{
	if (xx_yy[2] < 0)
	{
		if (fl)
			xx_yy[0] = xx_yy[0] - xx_yy[2] / k * (float)fl;
		xx_yy[2] = 0;
	}
	if (xx_yy[2] > (float)wsize[0])
	{
		if (fl)
			xx_yy[0] = xx_yy[0] + ((float)wsize[0] - xx_yy[2]) / k * (float)fl;
		xx_yy[2] = (float)wsize[0];
	}
	if (xx_yy[3] < 0)
	{
		if (fl)
			xx_yy[1] = xx_yy[1] - xx_yy[3] / k * (float)fl;
		xx_yy[3] = 0;
	}
	if (xx_yy[3] > (float)wsize[0])
	{
		if (fl)
			xx_yy[1] = xx_yy[1] + ((float)wsize[0] - xx_yy[3]) / k * (float)fl;
		xx_yy[3] = (float)wsize[0];
	}
}

int	crop_line(float xx_yy[4], int *wsize)
{
	int		flag;
	float	k;

	k = 0;
	if ((xx_yy[0] < 0 && xx_yy[1] < 0)
		|| (xx_yy[0] > (float)wsize[1] && xx_yy[1] > (float)wsize[1]))
		return (1);
	flag = 0;
	if (xx_yy[0] != xx_yy[1])
	{
		flag = 1;
		k = crop_x(xx_yy, wsize);
	}
	if ((xx_yy[2] < 0 && xx_yy[3] < 0)
		|| (xx_yy[2] > (float)wsize[0] && xx_yy[3] > (float)wsize[0]))
		return (1);
	crop_y(xx_yy, k, flag, wsize);
	return (0);
}

void	put_horiz_lines(t_img *pic, float ***v1, int *wsize, int *msize)
{
	int		h;
	int		w;
	float	xx_yy[4];

	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1] - 1)
		{
			xx_yy[0] = v1[0][h][w];
			xx_yy[1] = v1[0][h][w + 1];
			xx_yy[2] = v1[1][h][w];
			xx_yy[3] = v1[1][h][w + 1];
			if (!crop_line(xx_yy, wsize))
				put_line(pic, xx_yy);
			w++;
		}
		h++;
	}
}

void	put_vertic_lines(t_img *pic, float ***v1, int *wsize, int *msize)
{
	int		h;
	int		w;
	float	xx_yy[4];

	w = 0;
	while (w < msize[1])
	{
		h = 0;
		while (h < msize[0] - 1)
		{
			xx_yy[0] = v1[0][h][w];
			xx_yy[1] = v1[0][h + 1][w];
			xx_yy[2] = v1[1][h][w];
			xx_yy[3] = v1[1][h + 1][w];
			if (!crop_line(xx_yy, wsize))
				put_line(pic, xx_yy);
			h++;
		}
		w++;
	}
}

void	create_image(t_img *pic, float ***v1, int *wsize, int *msize)
{
	put_horiz_lines(pic, v1, wsize, msize);
	// put_vertic_lines(pic, v1, wsize, msize);
}

float	get_zmin(float **z, int *msize)
{
	int		h;
	int		w;
	float	min;

	h = 0;
	min = z[0][0];
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			if (z[h][w] < min)
				min = z[h][w];
			w++;
		}
		h++;
	}
	return (min);
}

float	get_persp_projection(float ***v1, float focal, int *wsize, int *msize)
{
	int		h;
	int		w;
	float	z;
	float	zmin;

	zmin = get_zmin(v1[2], msize);
	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			z = v1[2][h][w];
			v1[0][h][w] = -(focal * v1[0][h][w] / z) + (float)wsize[1] / 2;
			v1[1][h][w] = -(focal * v1[1][h][w] / z) + (float)wsize[0] / 2;
			v1[2][h][w] = focal;
			w++;
		}
		h++;
	}
	return (zmin);
}

float	get_isomet_projection(float ***v1, float focal, int *wsize, int *msize)
{
	int		h;
	int		w;
	float	zmin;

	zmin = get_zmin(v1[2], msize);
	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			v1[0][h][w] = (focal * v1[0][h][w] / zmin) + wsize[0] / 2;
			v1[1][h][w] = -(focal * v1[1][h][w] / zmin) + wsize[1] / 2;
			v1[2][h][w] = focal;
			w++;
		}
		h++;
	}
	return (zmin);
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
	float	zmin;

	put_white_back(&gen->pic, gen->mlx, gen->wsize);
	// print_ptr_array(gen->v1[0], gen->msize[0], gen->msize[1]);
	zmin = get_persp_projection(gen->v1, gen->focal, gen->wsize, gen->msize);
	// zmin = get_isomet_projection(gen->v1, gen->focal, gen->wsize, gen->msize);
	if (zmin > 0)
		create_image(&gen->pic, gen->v1, gen->wsize, gen->msize);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->pic.img);
}

void	set_defaults(t_mlx	*gen)
{
	gen->angles[0] = 0;
	gen->angles[1] = 0;
	gen->shift[0] = 0;
	gen->shift[1] = 0;
	gen->shift[2] = -15;
	gen->wsize[0] = 500;
	gen->wsize[1] = 700;
	gen->focal = gen->wsize[1] / tanf(60 * M_PI / 180 / 2) / 2;
}

int	main(void)
{
	t_mlx	gen;


	get_parsed(&gen.v1, &gen.v2, gen.msize, "maps/plat.fdf");
	set_defaults(&gen);
	move_cam(&gen, gen.shift, gen.angles, gen.msize);
	gen.angles[0] = 45;
	gen.angles[1] = 45;
	rotate_cam(gen.v2, gen.v1, gen.angles, gen.msize);
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, gen.wsize[1], gen.wsize[0], "Fdf");
	draw_map(&gen);
	// print_ptr_array(gen.v1[1], gen.msize[0], gen.msize[1]);
	mlx_loop(gen.mlx);
	exit (EXIT_SUCCESS);
}
