/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:42:09 by vados-sa          #+#    #+#             */
/*   Updated: 2024/10/30 18:42:12 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
