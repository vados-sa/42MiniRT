/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:42:42 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/10 16:54:16 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**split_check(char *line, t_data *data)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 6)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	return (info);
}

static void	populate_cy_node(t_object *node)
{
	node->type = 'c';
	node->cy.bottom_end_cap = vec_sub(node->cy.center, \
						vec_mult(node->cy.normal, node->cy.height / 2.0));
	node->cy.top_end_cap = vec_add(node->cy.center, \
						vec_mult(node->cy.normal, node->cy.height / 2.0));
}

int	parse_cy(t_data *data, char *line)
{
	t_object	*cy_node;
	char		**info;

	cy_node = new_object_node();
	if (!cy_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, cy_node);
	info = split_check(line, data);
	if (check_identifier(info[0], data, "object")
		|| check_coordinates(info[1], data, 'c')
		|| check_normal(info[2], data, 'c')
		|| check_dimension(info[3], CY_DIAM, data)
		|| check_dimension(info[4], CY_HEIGHT, data)
		|| check_color(info[5], data, 'c'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	cy_node->type = 'c';
	cy_node->cy.bottom_end_cap = vec_sub(cy_node->cy.center, \
					vec_mult(cy_node->cy.normal, cy_node->cy.height / 2.0));
	cy_node->cy.top_end_cap = vec_add(cy_node->cy.center, \
					vec_mult(cy_node->cy.normal, cy_node->cy.height / 2.0));
	return (0);
}
