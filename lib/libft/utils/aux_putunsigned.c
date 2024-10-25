/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_putunsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:57:42 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:27:52 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	aux_putunsigned(unsigned int n)
{
	int		i;

	i = 0;
	if (n >= 10)
	{
		i += aux_putunsigned(n / 10);
		i += aux_putunsigned(n % 10);
	}
	if (n <= 9)
	{
		i += aux_putchar(n + 48);
	}
	return (i);
}
