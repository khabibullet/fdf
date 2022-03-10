/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:18:32 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/21 20:19:02 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

int	ft_putnbr(int n)
{
	unsigned int	abs;
	int				count;

	count = 0;
	if (n < 0)
	{
		abs = (unsigned int)(-1 * n);
		count += ft_putchar('-');
	}
	else
		abs = (unsigned int)n;
	if (abs >= 10)
		count += ft_putnbr(abs / 10);
	count += ft_putchar(abs % 10 + '0');
	return (count);
}
