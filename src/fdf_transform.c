/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:49:19 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/07 18:36:27 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

void	get_transposed(float rot[3][3])
{
	float	buf;

	buf = rot[0][2];
	rot[0][2] = rot[2][0];
	rot[2][0] = buf;
	buf = rot[0][1];
	rot[0][1] = rot[1][0];
	rot[1][0] = buf;
	buf = rot[1][2];
	rot[1][2] = rot[2][1];
	rot[2][1] = buf;
}

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
}

void	rotate_cam(float ***v1, float ***v2, int *msize, float rot[3][3])
{
	int		h;
	int		w;

	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			v2[0][h][w] = rot[0][0] * v1[0][h][w]
				+ rot[0][1] * v1[1][h][w] + rot[0][2] * v1[2][h][w];
			v2[1][h][w] = rot[1][0] * v1[0][h][w]
				+ rot[1][1] * v1[1][h][w] + rot[1][2] * v1[2][h][w];
			v2[2][h][w] = rot[2][0] * v1[0][h][w]
				+ rot[2][1] * v1[1][h][w] + rot[2][2] * v1[2][h][w];
			w++;
		}
		h++;
	}
}

void	get_shifted(float ***v1, float *shift, int	*msize)
{
	int	h;
	int	w;

	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			v1[0][h][w] = v1[0][h][w] - shift[0];
			v1[1][h][w] = v1[1][h][w] - shift[1];
			v1[2][h][w] = v1[2][h][w] - shift[2];
			w++;
		}
		h++;
	}
}

/*
	** v1 = v1 - shift
	** v2 = rot * v1, rot = rot(fi, teta)
*/

void	move_cam(t_mlx	*gen, float *shift, int *msize, float rot[3][3])
{
	get_transposed(rot);
	get_shifted(gen->v1, shift, msize);
	rotate_cam(gen->v1, gen->v2, msize, rot);
}
