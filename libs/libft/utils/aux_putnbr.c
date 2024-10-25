/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:57:42 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:27:31 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	aux_putnbr(int nb)
{
	int		i;

	i = 0;
	if (nb == -2147483648)
	{
		return (write(1, "-2147483648", 11));
	}
	if (nb < 0)
	{
		i += aux_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		i += aux_putnbr(nb / 10);
		nb %= 10;
	}
	if (nb < 10)
		i += aux_putchar(nb + 48);
	return (i);
}
