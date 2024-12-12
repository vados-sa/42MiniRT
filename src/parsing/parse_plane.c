/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:48:29 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 17:00:15 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: parses information for the plane
 */
int	parse_pl(t_data *data, char *line)
{
	t_object	*pl_node;
	char		**info;

	pl_node = new_object_node();
	if (!pl_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, pl_node);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 4)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "object") || \
		check_coordinates(info[1], data, 'p') || \
		check_normal(info[2], data, 'p') || check_color(info[3], data, 'p'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	pl_node->type = 'p';
	return (0);
}
