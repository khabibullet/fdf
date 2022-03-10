/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:42:51 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/21 20:19:21 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

int	ft_putstr(char	*s)
{
	int	count;

	count = 0;
	if (s != NULL)
	{
		while (*s)
		{
			count += ft_putchar(*s);
			s++;
		}
	}
	else
		count += ft_putstr("(null)");
	return (count);
}
