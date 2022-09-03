/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 12:31:29 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/04 00:29:55 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	main(int argc, char **argv)
{
	t_mlx	gen;

	gen = (t_mlx){0};
	gen.wsize[HEIGHT] = 600;
	gen.wsize[WIDTH] = 600;
	get_parsed(argc, &gen, argv[1]);
	initialize_fdf(&gen);
	mlx_hook(gen.win, X_EVENT_KEY_PRESS, 0, &key_press, &gen);
	mlx_hook(gen.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gen);
	mlx_hook(gen.win, X_EVENT_EXIT, 0, &exit_hook, &gen);
	mlx_hook(gen.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook, &gen);
	mlx_loop_hook(gen.mlx, &main_loop, &gen);
	mlx_loop(gen.mlx);
	return (0);
}
