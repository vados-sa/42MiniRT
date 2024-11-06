
#include "minirt.h"

t_coord	ray_at(t_ray r, t_float t)
{
	return (vec_add(r.origin, vec_mult(r.direction, t)));
}

t_intersec	*plane_intersect(t_ray ray, t_object *obj)
{
	t_float		numerator;
	t_float		denominator;

	numerator = vec_dot(vec_sub(ray.origin,obj->pl.point), obj->pl.normal);
	denominator = vec_dot(ray.direction, obj->pl.normal);
	if (numerator == 0 && denominator == 0)
		return (NULL);
	else if (denominator == 0)
	{
		//? ray is inside of the plane
		obj->temp.color = obj->pl.color;
		obj->temp.t = 0;
		obj->temp.point = ray.origin;
		obj->temp.normal = obj->pl.normal;
	}
	else
	{
		obj->temp.color = obj->pl.color;
		obj->temp.t = numerator / denominator;
		obj->temp.point = ray_at(ray, obj->temp.t);
		obj->temp.normal = obj->pl.normal; // or is it something else?
	}
	return (&obj->temp);
}
