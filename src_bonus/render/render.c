/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:47:00 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/19 19:18:31 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	gradient(t_ray r, t_coord camera_up, t_data *data)
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


t_color	calculate_color(t_data *data, t_ray ray)
{
	t_color		col_rgb;
	t_intersec	*hit_rec;
	t_color		obj_color;

	hit_rec = intersection(data, ray);
	if (hit_rec)
	{
		obj_color = checkerboard(hit_rec);
		col_rgb = calculate_light(data, hit_rec, obj_color);
	}
	else
		col_rgb = gradient(ray, data->scene->c.up, data);
	return (col_rgb);
}

void	antialias(uint32_t x, uint32_t y, t_data *data)
{
	t_color			color;
	t_color			sub_color;
	uint32_t		i;
	uint32_t		j;
	t_ray			ray;

	color = col(0, 0, 0, 0);
	i = 0;
	while (i < ANTIALIAS_FACTOR)
	{
		j = 0;
		while (j < ANTIALIAS_FACTOR)
		{
			ray = create_ray(x + ((t_float)j / 5.0), y + ((t_float)i / 5.0), data->scene->c.center, data);
			sub_color = calculate_color(data, ray);
			color.r += sub_color.r;
			color.g += sub_color.g;
			color.b += sub_color.b;
			color.a += sub_color.a;
			j++;
		}
		i++;
	}
	color.r /= (ANTIALIAS_FACTOR * ANTIALIAS_FACTOR);
	color.g /= (ANTIALIAS_FACTOR * ANTIALIAS_FACTOR);
	color.b /= (ANTIALIAS_FACTOR * ANTIALIAS_FACTOR);
	color.a /= (ANTIALIAS_FACTOR * ANTIALIAS_FACTOR);
	mlx_put_pixel(data->image, x, y, create_color(color.r, color.g, color.b, color.a));
}

void	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	uint32_t	col_int;
	t_color		col_rgb;

	y = -1;
	while (++y < data->image_height)
	{
		x = -1;
		while (++x < data->image_width)
		{
			if (ANTIALIAS == 1)
				antialias(x, y, data);
			else
			{
				ray = create_ray(x, y, data->scene->c.center, data);
				col_rgb = calculate_color(data, ray);
				col_int = create_color(col_rgb.r, col_rgb.g, col_rgb.b, col_rgb.a);
				mlx_put_pixel(data->image, x, y, col_int);
			}
		}
	}
}

