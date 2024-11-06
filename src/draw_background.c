
#include "minirt.h"

uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	gradient(t_ray r, t_coord camera_up)
{
	t_coord	unit_direction;
	t_float	a;
	t_color	color;

	unit_direction = vec_unit(r.direction);
	a = 0.5 * (vec_dot(unit_direction, camera_up) + 1.0);
	color.r = ((1.0 - a) * 255 + a * 255);
	color.g = ((1.0 - a) * 255 + a * 182);
	color.b = ((1.0 - a) * 255 + a * 193);
	color.a = 255;
	return (color);
}

t_ray	create_ray(uint32_t x, uint32_t y, t_coord origin, t_data *data)
{
	t_ray	ray;
	t_coord	x_scaled;
	t_coord	y_scaled;
	t_coord	pixel_center;

	//ray.direction = (data->vp.pixel00 + (x * data->vp.pixel_x) + (y * data->vp.pixel_y));
	x_scaled = vec_mult(data->vp.pixel_x, x);
	y_scaled = vec_mult(data->vp.pixel_y, y);
	pixel_center = vec_add(vec_add(data->vp.pixel00, x_scaled), y_scaled);
	ray.direction = vec_sub(pixel_center, origin);
	ray.origin = origin;
	return (ray);
}

int	sphere_intersect(t_data *data, t_ray ray, t_object *obj)
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
		/* t_min = (-b - (sqrt(discriminant)) / 2 * a);
		t_max = (-b + (sqrt(discriminant)) / 2 * a);
		if (t_min >= 0)
			return (t_min); // sphere in front of the camera
		else if (t_max >= 0)
			return(t_max); // camera inside sphere */
	}
	else
		return (0);
}

void	put_color(t_color rgba, uint32_t x, uint32_t y, t_data *data)
{
	uint32_t	color;

	color = create_color(rgba.r, rgba.g, rgba.b, rgba.a);
	mlx_put_pixel(data->image, x, y, color);
}

int	intersection(t_data *data, t_ray ray, uint32_t x, uint32_t y)
{
	t_object	*object;
	t_object	*closest;

	object = data->scene->objects;
	closest = NULL;
	while (object)
	{
		if (object->type == 's')
			if (sphere_intersect(data, ray, object))
				closest = object; // object.sphere ?
		/* else if (object->type == 'p')
			plane_intersect();
		else if (object->type == 'c')
			cylinder_intersect();
		closest = compare_objects(object, closest); */
		object = object->next;
	}
	if (closest)
		return (put_color(closest->sp.color, x, y, data), 1);
	return (0);
}

void	draw_background(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	t_color		rgba;
	t_ray		ray;

	y = -1;
	while (++y < IMAGE_HEIGHT)
	{
		x = -1;
		while (++x < IMAGE_WIDTH)
		{
			ray = create_ray(x, y, data->scene->c.center, data);
			if (intersection(data, ray, x, y))
				continue ;
			else
			{
				rgba = gradient(ray, data->scene->c.up);
				color = create_color(rgba.r, rgba.g, rgba.b, rgba.a);
				//color = create_color(3, 4, 94, 255);
				mlx_put_pixel(data->image, x, y, color);
			}
		}
	}
}
