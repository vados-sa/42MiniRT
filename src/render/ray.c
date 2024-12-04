/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:14 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/04 14:45:15 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_coord	ray_at(t_ray r, t_float t)
{
	return (vec_add(r.origin, vec_mult(r.direction, t)));
}
