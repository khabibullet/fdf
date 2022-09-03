/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:32:12 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 12:33:43 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

void	draw_map(t_mlx	*gen)
{
	put_white_back(&gen->pic, gen->wsize);
	if (gen->proj_type == 0)
		get_persp_projection(gen->v1, gen->foc, gen->wsize, gen->msize);
	else
		get_isomet_projection(gen->v1, gen->foc, gen->wsize, gen->msize);
	put_horiz_lines(&gen->pic, gen->v1, gen->wsize, gen->msize);
	put_vertic_lines(&gen->pic, gen->v1, gen->wsize, gen->msize);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
	mlx_string_put(gen->mlx, gen->win, 10, 18, 0x00990000, gen->txt.str1);
	mlx_string_put(gen->mlx, gen->win, 10, 36, 0x00990000, gen->txt.str2);
	mlx_string_put(gen->mlx, gen->win, 10, 54, 0x00990000, gen->txt.str3);
	mlx_string_put(gen->mlx, gen->win, 10, 72, 0x00990000, gen->txt.str4);
}
