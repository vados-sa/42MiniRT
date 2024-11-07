
#include "minirt.h"

// it's still like the sphere. I need to understand the inifinite cylinder thingy.
t_intersec	*cylinder_intersect(t_ray ray, t_object *obj)
{
	t_float	t;

	t = find_t(ray, obj, 'c');
	if (t)
	{
		obj->temp.t = t;
		obj->temp.point = ray_at(ray, obj->temp.t);
		obj->temp.color = obj->cy.color;
		return (&obj->temp);
	}
	else
		return (NULL);
}
