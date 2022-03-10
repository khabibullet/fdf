/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:07:55 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/21 21:43:57 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

static int	put_var(const char	*format, va_list	ptr)
{
	int	count;

	count = 0;
	if (*format == '%')
		count += ft_putchar('%');
	else if (*format == 'c')
		count += ft_putchar(va_arg(ptr, int));
	else if (*format == 'd' || *format == 'i')
		count += ft_putnbr(va_arg(ptr, int));
	else if (*format == 'u')
		count += ft_putuint(va_arg(ptr, unsigned int));
	else if (*format == 'x' || *format == 'X')
		count += ft_puthex(va_arg(ptr, unsigned int), *format);
	else if (*format == 's')
		count += ft_putstr(va_arg(ptr, char *));
	else if (*format == 'p')
		count += ft_putptr(va_arg(ptr, void *));
	return (count);
}

int	ft_printf(const char	*format, ...)
{
	int		count;
	va_list	ptr;

	va_start(ptr, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			while (*format++)
			{
				count += put_var(format, ptr);
				if (*format == '%' || *format == 'c' || *format == 'd'
					|| *format == 'i' || *format == 'u' || *format == 'x'
					|| *format == 'X' || *format == 's' || *format == 'p')
					break ;
			}
		}
		else if (*format != '%')
			count += ft_putchar(*format);
		if (*format)
			format++;
	}
	return (count);
}
