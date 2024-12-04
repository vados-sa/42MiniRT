/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:47:10 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/04 14:47:43 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_coord	planar_map(t_coord plane, t_coord normal)
{
	t_float	u;
	t_float	v;

	if (fabs(normal.y) > EPSILON)
	{
		u = plane.x - floor(plane.x);
		v = plane.z - floor(plane.z);
	}
	else if (fabs(normal.x) > EPSILON)
	{
		u = plane.z - floor(plane.z);
		v = plane.y - floor(plane.y);
	}
	else if (fabs(normal.z) > EPSILON)
	{
		u = plane.x - floor(plane.x);
		v = plane.y - floor(plane.y);
	}
	return (coord(u, v, 0));
}

t_coord	spherical_map(t_coord point, t_float radius, t_coord normal)
{
	t_float	u;
	t_float	v;
	t_float	theta;
	t_float	phi;
	t_float	scale;

	scale = 10;
	theta = atan2(point.x, point.z);
	phi = acos(point.y / radius);
	u = theta / (2.0 * PI);
	u = 1.0 - (u + 0.5);
	v = 1 - phi / PI;
	u *= scale;
	v *= scale;
	return (coord(u, v, 0));
}

bool	checker_color(t_intersec *object)
{
	t_coord	uv;
	t_coord	relative_point;

	if (object->type == 'p' && CHECKP == 1)
		uv = planar_map(object->point, object->normal);
	else if (object->type == 's' && CHECKS == 1)
	{
		relative_point = vec_sub(object->point, object->self->sp.center);
		uv = spherical_map(relative_point, \
			object->self->sp.radius, object->normal);
	}
	else
		return (false);
	if (((int)floor(uv.x * 2) % 2) == ((int)floor(uv.y * 2) % 2))
		return (true);
	return (false);
}

t_color	checkerboard(t_intersec *object)
{
	t_color	black;
	t_color	white;

	black = object->color;
	white = col(abs(255 - black.r), abs(255 - black.g), \
				abs(255 - black.b), 255);
	if (checker_color(object))
		return (white);
	return (black);
}
