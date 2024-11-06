
#include "minirt.h"

int	intersection(t_data *data, t_ray ray, uint32_t x, uint32_t y)
{
	t_object	*object;
	t_intersec	*closest;
	t_intersec	*temp;

	//save in a hit_rec struct the point, the normal and the t value
	object = data->scene->objects;
	closest = NULL;
	while (object)
	{
		if (object->type == 's')
			temp = sphere_intersect(data, ray, object);
		else if (object->type == 'p')
			temp = plane_intersect();
		else if (object->type == 'c')
			temp = cylinder_intersect();
		closest = compare_records(temp, closest);
		object = object->next;
	}
	if (closest)
		return (put_color(closest->color, x, y, data), 1);
		//calculate the color based on the lights and the object
		//return the color
	return (0);
}
