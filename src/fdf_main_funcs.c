/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:49:58 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/06 21:05:46 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

void	draw_map(t_mlx	*gen)
{
	put_white_back(&gen->pic, gen->mlx, gen->wsize);
	if (gen->proj_type == 0)
		get_persp_projection(gen->v1, gen->foc, gen->wsize, gen->msize);
	else
		get_isomet_projection(gen->v1, gen->foc, gen->wsize, gen->msize);
	put_horiz_lines(&gen->pic, gen->v1, gen->wsize, gen->msize);
	put_vertic_lines(&gen->pic, gen->v1, gen->wsize, gen->msize);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->pic.img);
}

int	main_loop(t_mlx	*gen)
{
	get_rot_matrix(gen->rot, gen->angles);
	rotate_cam(gen->v2, gen->v1, gen->msize, gen->rot);
	move_cam(gen, gen->shift, gen->msize, gen->rot);
	draw_map(gen);
	return (0);
}
