/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_cap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:35 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/09 17:34:42 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

 //problem is here with the normals?
static int	intersect_cap_plane(t_ray ray, t_coord pl_point, \
							t_coord *pl_normal, t_float *t)
{
	t_float	denom;
	t_coord	oc;

	denom = vec_dot(ray.direction, *pl_normal);
	if (fabs(denom) > EPSILON)
	{
		oc = vec_sub(ray.origin, pl_point);
		*t = (-1 * vec_dot(oc, *pl_normal)) / denom;
		if (denom < 0)
			*pl_normal = *pl_normal;
		else
			*pl_normal = vec_mult(*pl_normal, -1.0);
		return (*t >= EPSILON);
	}
	return (0);
}

static int	is_within_radius(t_coord point, t_coord center, t_float radius)
{
	t_coord	diff;

	diff = vec_sub(point, center);
	if (vec_dot(diff, diff) <= (radius * radius))
		return (1);
	return (0);
}

/* t_intersec	*intersect_single_cap(t_ray ray, t_object *obj, t_float t)
{
	t_coord	point;
	t_float	t_temp;

	t_temp = t;
	if (intersect_cap_plane(ray, obj->cy.cap_center, &obj->cy.cap_normal, &t_temp))
	{
		point = ray_at(ray, t_temp);
		if (is_within_radius(point, obj->cy.cap_center, obj->cy.radius))
		{
			obj->temp.t = t_temp;
			obj->temp.point = point;
			obj->temp.color = obj->cy.color;
			obj->temp.normal = obj->cy.cap_normal;
			return (&obj->temp);
		}
	}
	return (NULL);
} */

t_intersec	*intersect_top_cap(t_ray ray, t_object *obj)
{
	t_coord	point;
	t_float	t_cap;
	t_float	denom;

	denom = vec_dot(ray.direction, obj->cy.normal);
	if (fabs(denom) <= EPSILON) // check if < instead
		return (NULL);
	t_cap = vec_dot(vec_sub(obj->cy.top_end_cap, ray.origin), obj->cy.normal) / denom;
	if (t_cap <= EPSILON) // check if just <
		return (NULL);
	point = ray_at(ray, t_cap);
	if (is_within_radius(point, obj->cy.top_end_cap, obj->cy.radius))
	{
		obj->cy.top.t = t_cap;
		obj->cy.top.point = point;
		obj->cy.top.color = obj->cy.color;
		obj->cy.top.normal = obj->cy.normal;
		return (&obj->cy.top);
	}
	return (NULL);
}

t_intersec	*intersect_bottom_cap(t_ray ray, t_object *obj)
{
	t_coord		point;
	t_float		t_cap;
	t_float		denom;

	denom = vec_dot(ray.direction, vec_mult(obj->cy.normal, -1));
	if (fabs(denom) <= EPSILON) // check if < instead
		return (NULL);
	t_cap = vec_dot(vec_sub(obj->cy.bottom_end_cap, ray.origin), vec_mult(obj->cy.normal, -1)) / denom;
	if (t_cap < EPSILON) // check if just <
		return (NULL);
	point = ray_at(ray, t_cap);
	if (is_within_radius(point, obj->cy.bottom_end_cap, obj->cy.radius))
	{
		obj->cy.bottom.t = t_cap;
		obj->cy.bottom.point = point;
		obj->cy.bottom.color = obj->cy.color;
		obj->cy.bottom.normal = vec_mult(obj->cy.normal, -1);
		return (&obj->cy.bottom);
	}
	return (NULL);
}

t_intersec	*intersect_cap(t_ray ray, t_object *obj)
{
	t_intersec	*top_cap;
	t_intersec	*bottom_cap;
	t_intersec	*cap;

	top_cap = intersect_top_cap(ray, obj);
	bottom_cap = intersect_bottom_cap(ray, obj);
	if (bottom_cap && top_cap)
	{
		cap = compare_distance(top_cap, bottom_cap, ray.origin);
		return (cap);
	}
	else if (bottom_cap)
		return (bottom_cap);
	else if (top_cap)
		return (top_cap);
	else
		return (NULL);
}
