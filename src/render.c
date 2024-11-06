
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

void	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	uint32_t	color;
	t_color		rgba;

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
