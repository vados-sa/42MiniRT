/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:42:09 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:58:32 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: a check before atof is applied on the string
 * to make the parsing strict.
 * We only accept digits, one sign and one precision point.
 */
int	float_check(char *str)
{
	int	i;
	int	dot_count;

	if (!str)
		return (1);
	if (!ft_isdigit(str[0]) && str[0] != '-' && str[0] != '+')
		return (1);
	i = 0;
	dot_count = 0;
	while (str[++i])
	{
		if (str[i] == '.')
			dot_count++;
		if ((str[i] != '.' && !ft_isdigit(str[i])) || dot_count > 1)
			return (1);
	}
	return (0);
}

/**
 * @brief: a check before atof is applied on the string
 * to make the parsing strict.
 * We only accept digits and one sign.
 */
int	int_check(char *str)
{
	int	i;

	if (!str)
		return (1);
	if (!ft_isdigit(str[0]) && str[0] != '-' && str[0] != '+')
		return (1);
	i = 0;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}
