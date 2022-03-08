/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:02:00 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/08 20:12:12 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_lib.h"

int	main(int argc, char **argv)
{
	t_mlx	gen;

	if (argc != 2)
	{
		ft_printf("Map error: Invalid arguments\n");
		return (1);
	}
	gen = (t_mlx){0};
	gen.wsize[0] = 500;
	gen.wsize[1] = 700;
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, gen.wsize[1], gen.wsize[0], "Fdf");
	get_parsed(&gen.v1, &gen.v2, gen.msize, argv[1]);
	set_defaults(&gen);
	mlx_hook(gen.win, X_EVENT_KEY_PRESS, 0, &key_press, &gen);
	mlx_hook(gen.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gen);
	mlx_hook(gen.win, X_EVENT_EXIT, 0, &exit_hook, &gen);
	mlx_hook(gen.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook, &gen);
	mlx_loop_hook(gen.mlx, &main_loop, &gen);
	mlx_loop(gen.mlx);
	return (0);
}
