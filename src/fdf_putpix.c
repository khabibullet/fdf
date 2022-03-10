/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_putpix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:59:38 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/07 21:24:19 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

void	my_mlx_pixel_put(t_img *pic, int x, int y, unsigned int color)
{
	char	*dst;

	dst = pic->addr + (y * pic->len + x * (pic->depth / 8));
	if (*(unsigned int *)dst == 0x00FFFFFF)
		*(unsigned int *)dst = color;
}

void	put_pixels_wu(t_img *pic, t_line ln)
{
	ln.x = roundf(ln.x) - 1;
	ln.ycur = roundf(ln.ycur) - 1;
	if (ln.x < 0)
		ln.x = 0;
	if (ln.ycur < 0)
		ln.ycur = 0;
	if (!ln.flag)
	{
		my_mlx_pixel_put(pic, (int)ln.x, (int)ln.ycur,
			0x00010101 * (int)(255 * ln.err / ln.dx));
		my_mlx_pixel_put(pic, (int)ln.x, (int)ln.ycur + ln.sgn,
			0x00010101 * (int)(255 * (1 - ln.err / ln.dx)));
	}
	else
	{
		my_mlx_pixel_put(pic, (int)ln.ycur, (int)ln.x,
			0x00010101 * (int)(255 * (ln.err / ln.dx)));
		my_mlx_pixel_put(pic, (int)ln.ycur + ln.sgn, (int)ln.x,
			0x00010101 * (int)(255 * (1 - ln.err / ln.dx)));
	}
}

void	swap_pairs(float *a1, float *a2, float *b1, float *b2)
{
	float	buf;

	buf = *a1;
	*a1 = *a2;
	*a2 = buf;
	if ((b1 != NULL) && (b1 != NULL))
	{
		buf = *b1;
		*b1 = *b2;
		*b2 = buf;
	}
}

void	swap_points(t_line	*ln, float xx_yy[4])
{
	ln->flag = 0;
	ln->x1 = xx_yy[0];
	ln->x2 = xx_yy[1];
	ln->y1 = xx_yy[2];
	ln->y2 = xx_yy[3];
	ln->dx = ln->x2 - ln->x1;
	ln->dy = ln->y2 - ln->y1;
	if (fabsf(ln->dy) > fabsf(ln->dx))
	{
		if (ln->dy > 0)
			swap_pairs(&ln->x1, &ln->y1, &ln->x2, &ln->y2);
		else if (ln->dy < 0)
		{
			swap_pairs(&ln->x1, &ln->y2, &ln->x2, &ln->y1);
			ln->dx *= -1;
			ln->dy *= -1;
		}
		swap_pairs(&ln->dx, &ln->dy, NULL, NULL);
		ln->flag = 1;
	}
}

void	put_line(t_img	*pic, float xx_yy[4])
{
	t_line	ln;

	swap_points(&ln, xx_yy);
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
