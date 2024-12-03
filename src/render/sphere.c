
#include "../incl/minirt.h"

t_float	find_discriminant(t_coord oc, t_float a, t_float b, t_float radius)
{
	t_float	c;
	t_float	discriminant;

	c = vec_dot(oc, oc) - (radius * radius);
	discriminant = (b * b) - (4.0 * a * c);
	return (discriminant);
}

t_float	t_max_or_min(t_float a, t_float b, t_float discriminant)
{
	t_float	t_min;
	t_float	t_max;

	t_min = (-b - (sqrt(discriminant))) / (2.0 * a);
	t_max = (-b + (sqrt(discriminant))) / (2.0 * a);
	if (t_min > EPSILON)
		return (t_min);
	else if (t_max >= EPSILON)
		return (t_max);
	else
		return (0);
}

t_float	find_t(t_ray ray, t_object *obj)
{
	t_coord	oc;
	t_float	discriminant;
	t_float	a;
	t_float	b;

	oc = vec_sub(obj->sp.center, ray.origin);
	a = vec_dot(ray.direction, ray.direction);
	b = -2.0 * vec_dot(ray.direction, oc);
	discriminant = find_discriminant(oc, a, b, obj->sp.radius);
	if (discriminant < 0.0)
		return (0);
	return (t_max_or_min(a, b, discriminant));
}

t_intersec	*sphere_intersect(t_data *data, t_ray ray, t_object *obj)
{
	t_float	t;

	t = find_t(ray, obj);
	if (t)
	{
		obj->temp.t = t;
		obj->temp.point = ray_at(ray, obj->temp.t);
		obj->temp.color = obj->sp.color;
		obj->temp.normal = vec_unit(vec_sub(obj->temp.point, obj->sp.center));
		obj->temp.type = 's';
		return (&obj->temp);
	}
	else
		return (NULL);
}
