/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:59:38 by anemesis          #+#    #+#             */
/*   Updated: 2022/01/14 21:55:57 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

int	ft_atoi(const char	*str)
{
	long	sum;
	long	lsum;
	int		sign;

	sum = 0;
	sign = 1;
	while (((9 <= *str) && (*str <= 13)) || (*str == ' '))
		str++;
	if (*str == '-')
		sign = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	while (ft_isdigit(*str))
	{
		lsum = sum;
		sum = 10 * sum + *str - '0';
		if (sum < lsum)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		str++;
	}
	return (sum * sign);
}
