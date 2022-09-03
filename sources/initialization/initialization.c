/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:16:16 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/04 00:20:40 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

void	initialize_fdf(t_mlx *gen)
{
	int height;
	int width;

	if (gen->wsize[0] < 600)
		height = 600;
	else
		height = gen->wsize[0];
	if (gen->wsize[1] < 193)
		width = 193;
	else
		width = gen->wsize[1] + 193;
	gen->mlx = mlx_init();
	gen->win = mlx_new_window(gen->mlx, width, height, "Fdf");
	gen->foc = gen->wsize[1] / tanf(60 * M_PI / 180 / 2) / 2;
	gen->mouse_sens = 0.5;
	gen->shift_sens = sqrt(powf(gen->msize[0], 2)
			+ powf(gen->msize[1], 2)) / 100;
	get_rot_matrix(gen->rot, (float [2]){0});
	move_cam(gen, (float [2]){0}, gen->msize, gen->rot);
	reset_cam_pos(gen);
	gen->pic.img = mlx_new_image(gen->mlx, width, height);
	gen->pic.addr = mlx_get_data_addr(gen->pic.img,
			&gen->pic.depth, &gen->pic.len, &gen->pic.end);
	width = 193;
	height = 600;
	gen->hint.img = mlx_xpm_file_to_image(gen->mlx, \
							"resources/hint_area.xpm", &width, &height);
	gen->hint.addr = mlx_get_data_addr(gen->hint.img, &gen->hint.depth, \
											&gen->hint.len, &gen->hint.end);
}