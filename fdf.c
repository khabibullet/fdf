/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/06 21:23:32 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_lib.h"

void	set_defaults(t_mlx	*gen)
{
	*gen = (t_mlx){0};
	gen->shift[2] = -15;
	gen->wsize[0] = 500;
	gen->wsize[1] = 700;
	gen->mouse_sens = 0.5;
	gen->shift_sens = 0.5;
	gen->foc = gen->wsize[1] / tanf(60 * M_PI / 180 / 2) / 2;
}

int	main(void)
{
	t_mlx	gen;

	set_defaults(&gen);
	get_parsed(&gen.v1, &gen.v2, gen.msize, "maps/plat.fdf");
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, gen.wsize[1], gen.wsize[0], "Fdf");
	get_rot_matrix(gen.rot, gen.angles);
	move_cam(&gen, gen.shift, gen.msize, gen.rot);
	gen.shift[2] = 0;
	mlx_hook(gen.win, X_EVENT_KEY_PRESS, 0, &key_press, &gen);
	mlx_hook(gen.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gen);
	mlx_hook(gen.win, X_EVENT_EXIT, 0, &exit_hook, &gen);
	mlx_hook(gen.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook, &gen);
	mlx_loop_hook(gen.mlx, &main_loop, &gen);
	mlx_loop(gen.mlx);
	exit (EXIT_SUCCESS);
}
