/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:27:08 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/04 14:43:01 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	int		sign;

	result = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*(str++) == '-')
			sign = -1;
	}
	while (*str && ft_isdigit(*str))
		result = result * 10.0 + (*(str++) - '0');
	if (*(str++) == '.')
	{
		while (*str && ft_isdigit(*str))
		{
			fraction = fraction * 10.0 + (*(str++) - '0');
			divisor *= 10.0;
		}
	}
	return (sign * (result + fraction / divisor));
}
