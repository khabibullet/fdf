/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:24:15 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 18:18:52 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

void	reset_cam_pos(t_mlx *gen)
{
	gen->proj_type = 1;
	gen->angles[0] = 135;
	gen->angles[1] = 45;
	get_centered(gen->v2[0], gen->msize);
	get_centered(gen->v2[1], gen->msize);
	get_centered(gen->v2[2], gen->msize);
	get_rot_matrix(gen->rot, gen->angles);
	rotate_cam(gen->v2, gen->v1, gen->msize, gen->rot);
	gen->shift[2] = -sqrt(powf(gen->msize[0], 2)
			+ powf(gen->msize[1], 2)) * 1.5;
	move_cam(gen, gen->shift, gen->msize, gen->rot);
	gen->shift[2] = 0;
}

void	get_centered(float **z, int *msize)
{
	int		h;
	int		w;
	float	zmid;

	zmid = (get_max(z, msize) + get_min(z, msize)) / 2;
	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			z[h][w] = z[h][w] - zmid;
			w++;
		}
		h++;
	}
}

void	change_proj(int *proj_type)
{
	if (*proj_type == 1)
		*proj_type = 0;
	else if (*proj_type == 0)
		*proj_type = 1;
}
