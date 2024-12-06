/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_cap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:35 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/06 12:57:05 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

static int	intersect_cap_plane(t_ray ray, t_coord pl_point, \
							t_coord pl_normal, t_float *t)
{
	t_float	denom;
	t_coord	oc;

	denom = vec_dot(pl_normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		oc = vec_sub(pl_point, ray.origin);
		*t = vec_dot(oc, pl_normal) / denom;
		return (*t >= 0);
	}
	return (0);
}

static int	is_within_radius(t_coord point, t_coord center, t_float radius)
{
	t_coord	diff;

	diff = vec_sub(point, center);
	return (vec_dot(diff, diff) <= radius * radius);
}

t_intersec	*intersect_single_cap(t_ray ray, t_object *obj, t_float t)
{
	t_coord	point;

	if (intersect_cap_plane(ray, obj->cy.cap_center, obj->cy.cap_normal, &t))
	{
		point = ray_at(ray, t);
		if (is_within_radius(point, obj->cy.cap_center, obj->cy.radius))
		{
			obj->temp.t = t;
			obj->temp.point = point;
			obj->temp.color = obj->cy.color;
			obj->temp.normal = obj->cy.cap_normal;
			return (&obj->temp);
		}
	}
	return (NULL);
}

t_intersec	*intersect_cap(t_ray ray, t_object *obj, t_float t)
{
	t_intersec	*top_cap;
	t_intersec	*bottom_cap;
	t_intersec	*cap;

	obj->cy.cap_center = obj->cy.top_end_cap;
	obj->cy.cap_normal = obj->cy.normal;
	top_cap = intersect_single_cap(ray, obj, t);
	obj->cy.cap_center = vec_add(obj->cy.top_end_cap, \
					vec_mult(obj->cy.normal, obj->cy.height)); // maybe height / 2
	obj->cy.cap_normal = vec_mult(obj->cy.normal, -1);
	bottom_cap = intersect_single_cap(ray, obj, t);
	if (top_cap && !bottom_cap)
		return (top_cap);
	else if (!top_cap && bottom_cap)
		return (bottom_cap);
	else if (top_cap && bottom_cap)
	{
		cap = compare_distance(top_cap, bottom_cap, ray.origin);
		return (cap);
	}
	else
		return (NULL);
}
