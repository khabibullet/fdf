/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_crop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:43:51 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 12:33:43 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

float	get_min(float **z, int *msize)
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

float	get_max(float **z, int *msize)
{
	int		h;
	int		w;
	float	max;

	h = 0;
	max = z[0][0];
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			if (z[h][w] > max)
				max = z[h][w];
			w++;
		}
		h++;
	}
	return (max);
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

void	crop_y(float xx_yy[4], float k, int fl, int *wsize)
{
	if (xx_yy[2] < 0)
	{
		if (fl)
			xx_yy[0] = xx_yy[0] - xx_yy[2] / k * (float)fl;
		xx_yy[2] = 0;
	}
	if (xx_yy[2] >= (float)wsize[0])
	{
		if (fl)
			xx_yy[0] = xx_yy[0] + ((float)wsize[0] - xx_yy[2]) / k * (float)fl;
		xx_yy[2] = (float)wsize[0] - 1;
	}
	if (xx_yy[3] < 0)
	{
		if (fl)
			xx_yy[1] = xx_yy[1] - xx_yy[3] / k * (float)fl;
		xx_yy[3] = 0;
	}
	if (xx_yy[3] >= (float)wsize[0])
	{
		if (fl)
			xx_yy[1] = xx_yy[1] + ((float)wsize[0] - xx_yy[3]) / k * (float)fl;
		xx_yy[3] = (float)wsize[0] - 1;
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
