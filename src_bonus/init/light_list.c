/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:46:43 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:58:03 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: allocates a new t_l node.
 * @returns the node or NULL on failure of allocation.
 */
t_l	*new_light_node(void)
{
	t_l	*new;

	new = (t_l *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/**
 * @brief: adds a node to the end of the t_l list.
 */
t_l	*light_last_node(t_l *light)
{
	t_l	*trav;

	if (!light)
		return (NULL);
	trav = light;
	while (trav->next)
		trav = trav->next;
	return (trav);
}

/**
 * @brief: loops through the t_l list to find the last node.
 * @returns the last node or NULL if there is none.
 */
void	add_light_node(t_l **light, t_l	*new)
{
	t_l	*tmp;

	if (light)
	{
		if (!*light)
			*light = new;
		else
		{
			tmp = light_last_node(*light);
			tmp->next = new;
		}
	}
}

/**
 * @brief: frees each node of the t_l list.
 * @param t_object **objects: the address of the head of the list.
 */
void	delete_light_list(t_l **lights)
{
	t_l	*post;
	t_l	*current;

	if (lights == NULL)
		return ;
	current = *lights;
	while (current != NULL)
	{
		post = current->next;
		free(current);
		current = post;
	}
	*lights = NULL;
}
