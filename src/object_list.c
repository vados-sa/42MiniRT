
#include "minirt.h"

t_object	*new_object_node(void)
{
	t_object	*new;

	new = (t_object *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

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
