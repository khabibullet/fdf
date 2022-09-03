/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:27:01 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 12:33:43 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

void	exit_fdf(t_mlx *gen)
{
	int	d;
	int	h;

	d = 0;
	while (d < 3)
	{
		h = 0;
		while (h < gen->msize[0])
		{
			free(gen->v1[d][h]);
			free(gen->v2[d][h]);
			h++;
		}
		free(gen->v1[d]);
		free(gen->v2[d]);
		d++;
	}
	mlx_destroy_image(gen->mlx, gen->pic.img);
	mlx_destroy_window(gen->mlx, gen->win);
	mlx_destroy_mlx(gen->mlx);
	exit (EXIT_SUCCESS);
}
