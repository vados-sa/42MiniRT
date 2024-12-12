/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:59 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 16:48:56 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: splits and arry into three arrays delimited by commas and spaces
 */
char	**split_three(char *info)
{
	int		i;
	int		comma_count;
	char	**str_arr;

	i = -1;
	comma_count = 0;
	while (info[++i])
	{
		if (info[i] == ',')
			comma_count++;
	}
	if (comma_count != 2)
		return (NULL);
	str_arr = ft_split(info, ',');
	if (ft_arr_len(str_arr) != 3)
		return (NULL);
	return (str_arr);
}

/**
 * @brief: creates a 3D-vector from 3 t_float values.
 */
t_coord	coord(t_float x, t_float y, t_float z)
{
	t_coord	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	return (xyz);
}

/**
 * @brief: assigns normals or points to objects, lights, or the camera.
 */
void	assign_xyz(char type, t_data *data, t_coord xyz, char coord_type)
{
	if (coord_type == 'n')
	{
		if (type == 'C')
			data->scene->c.orientation = vec_unit(xyz);
		if (type == 'p')
			object_last_node(data->scene->objects)->pl.normal = vec_unit(xyz);
		if (type == 'c')
			object_last_node(data->scene->objects)->cy.normal = vec_unit(xyz);
	}
	else if (coord_type == 'c')
	{
		if (type == 'C')
			data->scene->c.center = xyz;
		if (type == 'L')
			(light_last_node(data->scene->l))->point = xyz;
		if (type == 's')
			object_last_node(data->scene->objects)->sp.center = xyz;
		if (type == 'p')
			object_last_node(data->scene->objects)->pl.point = xyz;
		if (type == 'c')
			object_last_node(data->scene->objects)->cy.center = xyz;
	}
}

/**
 * @brief: assigns rgba values lights or objects
 * */
void	assign_rgba(char type, t_data *data, t_color rgba)
{
	if (type == 'A')
		data->scene->a.color = rgba;
	if (type == 'L')
		(light_last_node(data->scene->l))->color = rgba;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.color = rgba;
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.color = rgba;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.color = rgba;
}
