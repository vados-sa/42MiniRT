
#include "minirt.h"

/**
 * @var oc: vector from the ray origin to a point on the plane
 * @var numerator: numerator of the function to calculate t
 * @var denominator: denominator of the function to calculate t
 * if the denominator is close to 0, the ray will be parallel to the plane, so
 * they either perfectly coincide, offering an infinite number of solutions,
 * or they do not intersect at all. If t is negative, the intersection happens
 * nbehind the ray origin, which we don't want to take into consideration.
 * If the ray is coming from the back side of the plane, we want to invert the normal.
 * @return value: t_intersection struct if there is an intersection, NULL if there is not
 * or if the intersection happens behind the camera.
 */
t_intersec	*plane_intersect(t_ray ray, t_object *obj)
{
	t_float		numerator;
	t_float		denominator;
	t_coord		oc;

	obj->pl.normal = vec_unit(obj->pl.normal);
	oc = vec_sub(ray.origin, obj->pl.point);
	numerator = -1.0 * vec_dot(oc, obj->pl.normal);
	denominator = vec_dot(ray.direction, obj->pl.normal);
	if (fabs(denominator) < EPSILON) //ray is parallel to plane
		return (NULL);
	obj->temp.t = numerator / denominator;
	if (obj->temp.t <= EPSILON) //plane is behind ray
		return (NULL);
	obj->temp.color = obj->pl.color;
	obj->temp.point = ray_at(ray, obj->temp.t);
	//if (denominator < 0)
	//	obj->temp.normal = vec_unit(vec_mult(obj->pl.normal, -1.0));
	//else
		obj->temp.normal = vec_unit(obj->pl.normal);
	return (&obj->temp);
}
