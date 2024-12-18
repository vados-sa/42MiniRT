/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:48:37 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:58:52 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: splits the line by spaces.
 */
char	**info_split(char *line, t_data *data)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	return (info);
}

/**
 * @brief: parses information for the sphere
 */
int	parse_sp(t_data *data, char *line)
{
	t_object	*sp_node;
	char		**info;

	sp_node = new_object_node();
	if (!sp_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, sp_node);
	info = info_split(line, data);
	if (ft_arr_len(info) != 4)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "object")
		|| check_coordinates(info[1], data, 's')
		|| check_dimension(info[2], SP_DIAM, data)
		|| check_color(info[3], data, 's'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	sp_node->type = 's';
	return (0);
}
