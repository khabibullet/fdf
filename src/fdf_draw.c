/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:40:49 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/06 20:46:40 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

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

void	get_isomet_projection(float ***v1, float foc, int *wsize, int *msize)
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
			v1[0][h][w] = -(foc * v1[0][h][w] / zmin) + (float)wsize[1] / 2;
			v1[1][h][w] = -(foc * v1[1][h][w] / zmin) + (float)wsize[0] / 2;
			if (v1[2][h][w] < foc)
				v1[2][h][w] = 0;
			w++;
		}
		h++;
	}
}

void	get_persp_projection(float ***v1, float foc, int *wsize, int *msize)
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
			v1[0][h][w] = -(foc * v1[0][h][w] / z) + (float)wsize[1] / 2;
			v1[1][h][w] = -(foc * v1[1][h][w] / z) + (float)wsize[0] / 2;
			if (v1[2][h][w] <= 0)
				v1[2][h][w] = 0;
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
			if (!crop_line(xx_yy, wsize)
				&& (v1[2][h][w] != 0) && (v1[2][h + 1][w] != 0))
				put_line(pic, xx_yy);
			h++;
		}
		w++;
	}
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
			if (!crop_line(xx_yy, wsize)
				&& (v1[2][h][w] != 0) && (v1[2][h][w + 1] != 0))
				put_line(pic, xx_yy);
			w++;
		}
		h++;
	}
}
