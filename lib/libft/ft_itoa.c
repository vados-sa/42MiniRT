/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:51:18 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:33:03 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	aux_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	int				sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = aux_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
