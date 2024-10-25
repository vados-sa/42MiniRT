/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:47:04 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:28:49 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(int counter, va_list args, const char *str)
{
	if (*str == 'c')
		counter += aux_putchar(va_arg(args, int));
	if (*str == 's')
		counter += aux_putstr(va_arg(args, char *));
	if (*str == 'p')
		counter += aux_putptr(va_arg(args, unsigned long long));
	if (*str == 'i' || *str == 'd')
		counter += aux_putnbr(va_arg(args, int));
	if (*str == 'u')
		counter += aux_putunsigned(va_arg(args, unsigned int));
	if (*str == 'x' || *str == 'X')
		counter += aux_puthex(*str, va_arg(args, unsigned int));
	if (*str == '%')
		counter += aux_putchar('%');
	return (counter);
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	va_list	args;

	va_start(args, str);
	counter = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str != '%')
			counter += aux_putchar(*str);
		else if (*str == '%' && ++str)
		{
			counter = ft_format(counter, args, str);
		}
		str++;
	}
	va_end(args);
	return (counter);
}
