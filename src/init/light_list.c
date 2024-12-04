/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:46:43 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/04 14:46:44 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_l	*new_light_node(void)
{
	t_l	*new;

	new = (t_l *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

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
