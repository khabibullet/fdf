/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:39:35 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/21 20:19:14 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

int	ft_putptr(void *p)
{
	int			rem;
	uintptr_t	n;
	int			flag;
	int			count;

	count = 0;
	flag = 0;
	n = (uintptr_t)p;
	if (n >= 16)
	{
		flag = 1;
		count += ft_putptr((void *)(n / 16));
	}
	if (!flag)
		count += ft_putstr("0x");
	rem = n % 16;
	if (rem > 9)
		rem = rem - 10 + 'a';
	else
		rem = rem + '0';
	count += ft_putchar(rem);
	return (count);
}
