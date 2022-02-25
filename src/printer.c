/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:49:17 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/25 18:52:56 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

void	print_ptr_array(float	**arr, int h, int w)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < h)
	{
		x = 0;
		c = ' ';
		while (x < w)
		{
			if (x == w - 1)
				c = '\n';
			printf("%.1f%c", arr[y][x], c);
			x++;
		}
		y++;
	}
}

void	print_3x3_array(float arr[3][3])
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < 3)
	{
		x = 0;
		c = ' ';
		while (x < 3)
		{
			if (x == 2)
				c = '\n';
			printf("%.1f%c", arr[y][x], c);
			x++;
		}
		y++;
	}
}
