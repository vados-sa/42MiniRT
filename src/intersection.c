
#include "minirt.h"

void	put_color(t_intersec *hit_rec, uint32_t x, uint32_t y, t_data *data)
{
	uint32_t	col_int;
	t_color		col_rgb;

	ambient_light(data->scene->a);
	diffuse_light(data->scene->l, hit_rec);
	col_rgb = calculate_light(data, hit_rec, hit_rec->color);
	col_int = create_color(col_rgb.r, col_rgb.g, col_rgb.b, col_rgb.a);
	mlx_put_pixel(data->image, x, y, col_int);
}

t_intersec	*compare_distance(t_intersec *obj_1, t_intersec *obj_2, \
								t_coord origin)
{
	t_float	d1;
	t_float	d2;

	if (!obj_2)
		return(obj_1);
	if (!obj_1)
		return (obj_2);
	d1 = sqrt(pow((obj_1->point.x - origin.x), 2) +
				pow((obj_1->point.y - origin.y), 2) +
				pow((obj_1->point.z - origin.z), 2));
	d2 = sqrt(pow((obj_2->point.x - origin.x), 2) +
				pow((obj_2->point.y - origin.y), 2) +
				pow((obj_2->point.z - origin.z), 2));
	if (d1 <= d2)
		return (obj_1);
	else
		return (obj_2);
}

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

	t_min = (-b - (sqrt(discriminant)) / 2 * a);
	t_max = (-b + (sqrt(discriminant)) / 2 * a);
	if (t_min >= 0)
		return (t_min);
	else if (t_max >= 0)
		return (t_max);
	else
		return (0);
}

t_float	find_t(t_ray ray, t_object *obj, char type)
{
	t_coord	oc;
	t_float	discriminant;
	t_float	a;
	t_float	b;

	if (type == 's')
		oc = vec_sub(obj->sp.center, ray.origin);
	else if (type == 'c')
		oc = vec_sub(obj->cy.center, ray.origin);
	a = vec_dot(ray.direction, ray.direction);
	b = -2.0 * vec_dot(ray.direction, oc);
	if (type == 's')
		discriminant = find_discriminant(oc, a, b, obj->sp.radius);
	else if (type == 'c')
		discriminant = find_discriminant(oc, a, b, obj->cy.radius);
	if (discriminant < 0)
		return (0);
	return (t_max_or_min(a, b, discriminant));
}

t_intersec	*sphere_intersect(t_data *data, t_ray ray, t_object *obj)
{
	t_float	t;

	t = find_t(ray, obj, 's');
	if (t)
	{
		obj->temp.t = t;
		obj->temp.point = ray_at(ray, obj->temp.t);
		obj->temp.color = obj->sp.color;
		obj->temp.normal = vec_unit(vec_sub(obj->temp.point, obj->sp.center));
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
			temp = plane_intersect(ray, object);
		else if (object->type == 'c')
			temp = cylinder_intersect(ray, object);
		closest = compare_distance(temp, closest, ray.origin);
		object = object->next;
	}
	if (closest)
		return (put_color(closest, x, y, data), 1);
		//calculate the color based on the lights and the object
		//return the color
		//free(closest);
	return (0);
}


/* int	sphere_intersect(t_data *data, t_ray ray, t_object *obj)
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
	discriminant = (b * b) - (4 * a * c);
	if (discriminant >= 0)
	{
		return (1);
		t_min = (-b - (sqrt(discriminant)) / 2 * a);
		t_max = (-b + (sqrt(discriminant)) / 2 * a);
		if (t_min >= 0)
			return (t_min); // sphere in front of the camera
		else if (t_max >= 0)
			return(t_max); // camera inside sphere
	}
	else
		return (0);
}

int	intersection(t_data *data, t_ray ray, uint32_t x, uint32_t y)
{
	t_object	*object;
	t_object	*closest;

	//save in a hit_rec struct the point, the normal and the t value
	object = data->scene->objects;
	closest = NULL;
	while (object)
	{
		if (object->type == 's')
			if (sphere_intersect(data, ray, object))
				closest = object; // object.sphere ?
		 else if (object->type == 'p')
			plane_intersect();
		else if (object->type == 'c')
			cylinder_intersect();
		closest = compare_objects(object, closest);
		object = object->next;
	}
	if (closest)
		return (put_color(closest->sp.color, x, y, data), 1);
		//calculate the color based on the lights and the object
		//return the color
	return (0);
} */
