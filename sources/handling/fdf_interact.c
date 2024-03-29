/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_interact.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:16:47 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 12:33:43 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

int	mouse_hook(int x2, int y2, t_mlx *gen)
{
	static int	flag;
	static int	x1;
	static int	y1;

	if (flag)
	{
		gen->angles[0] += ((float)(x1 - x2)) * gen->mouse_sens;
		gen->angles[1] += ((float)(y1 - y2)) * gen->mouse_sens;
		if (gen->angles[0] > 360)
			gen->angles[0] -= 360;
		else if (gen->angles[0] < -360)
			gen->angles[0] += 360;
		if (gen->angles[1] > 360)
			gen->angles[1] -= 360;
		else if (gen->angles[1] < -360)
			gen->angles[1] += 360;
	}
	x1 = x2;
	y1 = y2;
	flag = 1;
	return (0);
}

void	limit_shift(t_mlx *gen)
{
	if (gen->shift[0] > gen->shift_sens)
		gen->shift[0] = gen->shift_sens;
	if (gen->shift[0] < -gen->shift_sens)
		gen->shift[0] = -gen->shift_sens;
	if (gen->shift[1] > gen->shift_sens)
		gen->shift[1] = gen->shift_sens;
	if (gen->shift[1] < -gen->shift_sens)
		gen->shift[1] = -gen->shift_sens;
	if (gen->shift[2] > gen->shift_sens)
		gen->shift[2] = gen->shift_sens;
	if (gen->shift[2] < -gen->shift_sens)
		gen->shift[2] = -gen->shift_sens;
}

int	key_press(int keycode, t_mlx *gen)
{
	if (keycode == KEY_D)
		gen->shift[0] += -gen->shift_sens;
	else if (keycode == KEY_A)
		gen->shift[0] += gen->shift_sens;
	else if (keycode == KEY_W)
		gen->shift[2] += gen->shift_sens;
	else if (keycode == KEY_S)
		gen->shift[2] += -gen->shift_sens;
	else if (keycode == KEY_E)
		gen->shift[1] += gen->shift_sens;
	else if (keycode == KEY_Q)
		gen->shift[1] += -gen->shift_sens;
	else if (keycode == KEY_PLUS)
		gen->shift_sens *= 1.2;
	else if (keycode == KEY_MINUS)
		gen->shift_sens /= 1.2;
	else if (keycode == KEY_P)
		change_proj(&gen->proj_type);
	else if (keycode == KEY_R)
		reset_cam_pos(gen);
	else if (keycode == KEY_ESC)
		exit_fdf(gen);
	limit_shift(gen);
	return (0);
}

int	key_release(int keycode, t_mlx *gen)
{
	if (keycode == KEY_D)
		gen->shift[0] -= -gen->shift_sens;
	else if (keycode == KEY_A)
		gen->shift[0] -= gen->shift_sens;
	else if (keycode == KEY_W)
		gen->shift[2] -= gen->shift_sens;
	else if (keycode == KEY_S)
		gen->shift[2] -= -gen->shift_sens;
	else if (keycode == KEY_E)
		gen->shift[1] -= gen->shift_sens;
	else if (keycode == KEY_Q)
		gen->shift[1] -= -gen->shift_sens;
	return (0);
}

int	exit_hook(t_mlx *gen)
{
	exit_fdf(gen);
	return (0);
}
