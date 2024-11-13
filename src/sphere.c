
#include "../incl/minirt.h"

t_float	find_discriminant(t_coord oc, t_float a, t_float b, t_float radius)
{
	t_float	c;
	t_float	discriminant;

	c = vec_dot(oc, oc) - (radius * radius);
	discriminant = (b * b) - (4 * a * c);
	return (discriminant);
}

t_float	t_max_or_min(t_float a, t_float b, t_float discriminant)
{
	t_float	t_min;
	t_float	t_max;

	t_min = (-b - (sqrt(discriminant))) / (2 * a);
	t_max = (-b + (sqrt(discriminant))) / (2 * a);
	if (t_min > 0)
		return (t_min);
	else if (t_max >= 0)
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
	if (discriminant < 0)
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
		obj->temp.normal = vec_unit(vec_sub(obj->sp.center, obj->temp.point));
		return (&obj->temp);
	}
	else
		return (NULL);
}

/* t_intersec	*sphere_intersect(t_data *data, t_ray ray, t_object *obj)
{
	t_float	discriminant;
	t_float	a;
	t_float	b;
	t_float	c;
	t_coord	oc;
	t_float	t_min;
	t_float	t_max;

	oc = vec_sub(obj->sp.center, ray.origin);
	a = vec_dot(ray.direction, ray.direction);
	b = -2.0 * vec_dot(ray.direction, oc);
	c = vec_dot(oc, oc) - (obj->sp.radius * obj->sp.radius);
	discriminant = (b * b) - (4.0 * a * c);
	if (discriminant >= 0)
	{
		t_min = (-b - (sqrt(discriminant)) / 2.0 * a);
		t_max = (-b + (sqrt(discriminant)) / 2.0 * a);
		if (t_min >= 0)
			obj->temp.t = t_min; // sphere in front of the camera
		else if (t_max >= 0)
			obj->temp.t = t_max; // camera inside sphere
		else
			return (NULL);
		obj->temp.point = ray_at(ray, obj->temp.t);
		//obj->temp.normal = find_normal();
		obj->temp.color = obj->sp.color;
		return (&obj->temp);
	}
	else
		return (NULL);
} */
