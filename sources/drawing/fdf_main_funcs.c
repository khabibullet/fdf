/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:49:58 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/01 18:37:37 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf_lib.h"

int	main_loop(t_mlx	*gen)
{
	get_rot_matrix(gen->rot, gen->angles);
	rotate_cam(gen->v2, gen->v1, gen->msize, gen->rot);
	move_cam(gen, gen->shift, gen->msize, gen->rot);
	draw_map(gen);
	return (0);
}
