/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:14 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:59:37 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @return: a t_ray ray originating at the camera´s position and
 * directed towards the center of the windows's pixel at width x and height y,
 * translated into viewport dimensions. The calculation starts at pixel00.
 */
t_ray	create_ray(uint32_t x, uint32_t y, t_coord origin, t_data *data)
{
	t_ray	ray;
	t_coord	x_scaled;
	t_coord	y_scaled;
	t_coord	pixel_center;

	x_scaled = vec_mult(data->vp.pixel_x, x);
	y_scaled = vec_mult(data->vp.pixel_y, y);
	pixel_center = vec_add(vec_add(data->vp.pixel00, x_scaled), y_scaled);
	ray.direction = vec_sub(pixel_center, origin);
	ray.origin = origin;
	return (ray);
}

/**
 * @brief: much used function to determine the point on
 * the ray which is at distance t from the ray's origin
 */
t_coord	ray_at(t_ray r, t_float t)
{
	return (vec_add(r.origin, vec_mult(r.direction, t)));
}
