/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:20 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:36:24 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && i < n - 1)
		i++;
	if (n == 0)
		return (0);
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else
		return (0);
}
