
#include "minirt.h"

t_coord	ray_at(t_ray r, t_float t)
{
	return (vec_add(r.origin, vec_mult(r.direction, t)));
}

/*If the plane and ray are parallel (i.e., when approaches 0),
they either perfectly coincide, offering an infinite number of solutions,
or they do not intersect at all. In practical C++ implementations,
we typically return false (indicating no intersection)
when the denominator is less than a very small threshold.*/
t_intersec	*plane_intersect(t_ray ray, t_object *obj)
{
	t_float		numerator;
	t_float		denominator;
	t_float		D;

	D = vec_dot(obj->pl.normal, obj->pl.point);
	numerator = D - vec_dot(obj->pl.normal, ray.origin);
	denominator = vec_dot(obj->pl.normal, ray.direction);
	if (numerator == 0 || fabs(denominator) < 1e-6) //parallel plane: 1. no intersection 2. infinite intersections, ray inside plane
		return (NULL);
	else
	{
		obj->temp.color = obj->pl.color;
		obj->temp.t = numerator / denominator;
		obj->temp.point = ray_at(ray, obj->temp.t);
		if (denominator > 0)
			obj->temp.normal = vec_mult(obj->pl.normal, -1.0); //if ray intersects from the back, invert normal
		else
			obj->temp.normal = obj->pl.normal;
	}
	return (&obj->temp);
}
