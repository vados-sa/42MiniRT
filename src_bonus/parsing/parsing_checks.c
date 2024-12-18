/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:55 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:58:59 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: checks if the rgb values are correct, transforms them into integers,
 * stores them in a struct and assigns them to a light or object.
 * @returns 1 on error and 0 on success.
 */
int	check_color(char *info, t_data *data, char type)
{
	char	**color;
	int		i;
	int		j;
	t_color	rgba;

	color = split_three(info);
	if (!color)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (int_check(color[0]) || int_check(color[1]) || int_check(color[2]))
	{
		free_arr(color, NULL);
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	}
	rgba = col(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]), 255);
	free_arr(color, NULL);
	if ((rgba.r < 0 || rgba.r > 255) || (rgba.g < 0 || rgba.g > 255)
		|| (rgba.b < 0 || rgba.b > 255))
		return (ft_putendl_fd(COL_RANGE_ERR, 2), 1);
	assign_rgba(type, data, rgba);
	return (0);
}

int	check_identifier(char *info, t_data *data, char *type)
{
	if (!ft_strcmp(type, "element") && info[1])
		return (ft_putendl_fd(TYPE_ID_ERR, 2), 1);
	else if (!ft_strcmp(type, "object") && info[2])
		return (ft_putendl_fd(TYPE_ID_ERR, 2), 1);
	return (0);
}

/**
 * @brief: checks if the coordinate values are correct and normalized,
 * transforms them into floats,
 * stores them in a struct and assigns them to a light, camera or object.
 * @returns 1 on error and 0 on success.
 */
int	check_normal(char *info, t_data *data, char type)
{
	char			**coordinates;
	int				i;
	int				j;
	t_coord			xyz;

	coordinates = split_three(info);
	if (!coordinates)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (float_check(coordinates[0]) || float_check(coordinates[1])
		|| float_check(coordinates[2]))
	{
		free_arr(coordinates, NULL);
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	}
	xyz = coord(ft_atof(coordinates[0]), ft_atof(coordinates[1]),
			ft_atof(coordinates[2]));
	free_arr(coordinates, NULL);
	if (vec_len(xyz) > (1.0 + EPSILON) || vec_len(xyz) < (1.0 - EPSILON))
		return (ft_putendl_fd(NORMAL_RANGE_ERR, 2), 1);
	assign_xyz(type, data, xyz, 'n');
	return (0);
}

/**
 * @brief: checks if the coordinate values are correct,
 * transforms them into floats,
 * stores them in a struct and assigns them to a light, camera or object.
 * @returns 1 on error and 0 on success.
 * */
int	check_coordinates(char *info, t_data *data, char type)
{
	char			**coordinates;
	int				i;
	int				j;
	t_coord			xyz;

	coordinates = split_three(info);
	if (!coordinates)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (float_check(coordinates[0]) || float_check(coordinates[1])
		|| float_check(coordinates[2]))
	{
		free_arr(coordinates, NULL);
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	}
	xyz = coord(ft_atof(coordinates[0]), ft_atof(coordinates[1]),
			ft_atof(coordinates[2]));
	free_arr(coordinates, NULL);
	assign_xyz(type, data, xyz, 'c');
	return (0);
}

/**
 * @brief: checks if the radius or height value is correct,
 * transforms it into float,
 * and assigns it to a sphere or cylinder.
 * @returns 1 on error and 0 on success.
 */
int	check_dimension(char *line, t_dimension type, t_data *data)
{
	t_float	dimension;

	if (float_check(line))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	dimension = ft_atof(line);
	if (dimension <= 0.0)
		return (ft_putendl_fd(DIMENSION_ERR, 2), 1);
	if (type == CY_DIAM)
		object_last_node(data->scene->objects)->cy.radius = dimension / 2.0;
	if (type == CY_HEIGHT)
		object_last_node(data->scene->objects)->cy.height = dimension;
	if (type == SP_DIAM)
		object_last_node(data->scene->objects)->sp.radius = dimension / 2.0;
	return (0);
}
