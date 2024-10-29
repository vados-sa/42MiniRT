
#include "minirt.h"


t_L	*new_light_node(void)
{
	t_L	*new;

	new = (t_L *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_L	*light_last_node(t_L *light)
{
	t_L	*trav;

	if (!light)
		return (NULL);
	trav = light;
	while (trav->next)
		trav = trav->next;
	return (trav);
}

void	add_light_node(t_L **light, t_L	*new)
{
	t_L	*tmp;

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
