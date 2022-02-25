/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:16:47 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/25 19:27:49 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

// int	close_win(int keycode, t_mlx	*gen)
// {
// 	if (keycode == 53)
// 	{
// 		mlx_destroy_window(gen->mlx, gen->win);
// 		exit(0);
// 	}
// 	return (0);
// }

// int	interact(t_mlx *gen)
// {
// 	// mlx_loop_hook(gen.mlx, rotate, &gen);
// 	// mlx_hook(gen.win, 6, 0, mouse_move, &gen);
// 	// mlx_hook(gen.win, 2, 0, rot_off, &gen);
// 	// mlx_hook(gen->win, 4, 0, mouse_press, gen);
// 	mlx_hook(gen->win, 17, 0, close_win, gen);
// 	return (0);
// }

// int mouse_move(int x, int y, t_mlx *gen)
// {
// 	(void)gen;
// 	printf("%d - %d\n", x, y);
// 	return (0);
// }