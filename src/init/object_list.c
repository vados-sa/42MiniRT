/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:46:39 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/13 09:57:58 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: allocates a new t_object node.
 * @returns the node or NULL on failure of allocation.
 */
t_object	*new_object_node(void)
{
	t_object	*new;

	new = (t_object *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/**
 * @brief: adds a node to the end of the t_object list.
 */
void	add_object_node(t_object **object, t_object	*new)
{
	t_object	*tmp;

	if (object)
	{
		if (!*object)
			*object = new;
		else
		{
			tmp = object_last_node(*object);
			tmp->next = new;
		}
	}
}

/**
 * @brief: loops through the t_object list to find the last node.
 * @returns the last node or NULL if there is none.
 */
t_object	*object_last_node(t_object *head)
{
	t_object	*trav;

	if (!head)
		return (NULL);
	trav = head;
	while (trav->next)
		trav = trav->next;
	return (trav);
}

/**
 * @brief: frees each node of the t_object list.
 * @param t_object **objects: the address of the head of the list.
 */
void	delete_object_list(t_object **objects)
{
	t_object	*post;
	t_object	*current;

	if (objects == NULL)
		return ;
	current = *objects;
	while (current != NULL)
	{
		post = current->next;
		free(current);
		current = post;
	}
	*objects = NULL;
}
