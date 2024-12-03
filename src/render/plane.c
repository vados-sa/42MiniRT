
#include "minirt.h"

t_intersec	*plane_intersect(t_ray ray, t_object *obj)
{
	t_float		numerator;
	t_float		denominator;
	t_coord		oc;

	obj->pl.normal = vec_unit(obj->pl.normal);
	oc = vec_sub(ray.origin, obj->pl.point);
	numerator = -1.0 * vec_dot(oc, obj->pl.normal);
	denominator = vec_dot(ray.direction, obj->pl.normal);
	if (fabs(denominator) < EPSILON)
		return (NULL);
	obj->temp.t = numerator / denominator;
	if (obj->temp.t <= EPSILON)
		return (NULL);
	obj->temp.color = obj->pl.color;
	obj->temp.point = ray_at(ray, obj->temp.t);
	if (denominator < 0)
		obj->temp.normal = vec_unit(obj->pl.normal);
	else
		obj->temp.normal = vec_unit(vec_mult(obj->pl.normal, -1.0));
	obj->temp.type = 'p';
	return (&obj->temp);
}
