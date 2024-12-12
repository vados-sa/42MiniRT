/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:48:21 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 17:00:32 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: checks the light ratio and stores it.
 */
static int	check_ratio(char *info, t_data *data, char type)
{
	t_float	ratio;

	if (float_check(info))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	ratio = ft_atof(info);
	if (ratio < 0.0 || ratio > 1.0)
		return (ft_putendl_fd(RATIO_ERR, 2), 1);
	if (type == 'A')
		data->scene->a.ratio = ratio;
	else
		(light_last_node(data->scene->l))->brightness = ratio;
	return (0);
}

/**
 * @brief: parses information for the ambient lighting
 */
int	parse_a(t_data *data, char *line)
{
	char	**info;
	int		i;

	if (line[ft_strlen(line)] == ' ')
		ft_exit(1, data, SPACE_ERR);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 3)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "element")
		|| check_ratio(info[1], data, 'A') || check_color(info[2], data, 'A'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	return (1);
}

/**
 * @brief: parses information for the lighting
 */
int	parse_l(t_data *data, char *line)
{
	char	**info;
	t_l		*node;

	node = new_light_node();
	if (!node)
		ft_exit(1, data, ALLOC_ERR);
	add_light_node(&data->scene->l, node);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 4)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "element")
		|| check_coordinates(info[1], data, 'L')
		|| check_ratio(info[2], data, 'L')
		|| check_color(info[3], data, 'L'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	return (1);
}
