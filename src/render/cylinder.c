/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:31 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/09 17:33:31 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

static t_float	find_discriminant(t_ray ray, t_object *obj, t_float a, \
t_float b)
{
	t_float	c;

	c = vec_dot(vec_sub(ray.origin, obj->cy.bottom_end_cap), vec_sub(ray.origin, \
		obj->cy.bottom_end_cap)) - vec_dot(vec_sub(ray.origin, \
		obj->cy.bottom_end_cap), obj->cy.normal) * \
		vec_dot(vec_sub(ray.origin, obj->cy.bottom_end_cap), \
		obj->cy.normal) - obj->cy.radius * obj->cy.radius;
	return (b * b - 4 * a * c);
}

static t_float	find_t_cy(t_ray ray, t_object *obj) //problem here?
{
	t_float	discriminant;
	t_float	a;
	t_float	b;
	t_float	t_max;
	t_float	t_min;
	t_float m1;
	t_float	m2;

	a = vec_dot(ray.direction, ray.direction) - vec_dot(ray.direction, \
		obj->cy.normal) * vec_dot(ray.direction, obj->cy.normal);
	b = 2 * (vec_dot(ray.direction, vec_sub(ray.origin, obj->cy.bottom_end_cap)) - \
		vec_dot(ray.direction, obj->cy.normal) * vec_dot(vec_sub(ray.origin, \
		obj->cy.bottom_end_cap), obj->cy.normal));
	discriminant = find_discriminant(ray, obj, a, b);
	if (discriminant < 0)
		return (-1.0);
	t_min = (-b - (sqrt(discriminant))) / (2.0 * a);
	t_max = (-b + (sqrt(discriminant))) / (2.0 * a);
	m1 = vec_dot(ray.direction, obj->cy.normal) * t_min + \
		vec_dot(vec_sub(ray.origin, obj->cy.bottom_end_cap), obj->cy.normal);
	m2 = vec_dot(ray.direction, obj->cy.normal) * t_max + \
		vec_dot(vec_sub(ray.origin, obj->cy.bottom_end_cap), obj->cy.normal);
	if (t_min > t_max && t_min > EPSILON && (m2 >= EPSILON && m2 <= obj->cy.height))
		return (t_max);
	else  if (t_min > EPSILON && (m1 >= EPSILON && m1 <= obj->cy.height))
		return (t_min);
	else if (t_max >= EPSILON && (m2 >= EPSILON && m2 <= obj->cy.height))
		return (t_max);
	else
		return (-1.0);
}

t_intersec	*cy_body_intersect(t_ray ray, t_object *obj)
{
	t_float	t;
	t_float	m;

	t = find_t_cy(ray, obj);
	if (t == -1.0)
		return (NULL);
	m = vec_dot(ray.direction, obj->cy.normal) * t + \
		vec_dot(vec_sub(ray.origin, obj->cy.bottom_end_cap), obj->cy.normal);
	//if (m < EPSILON || m > obj->cy.height)
	//	return (NULL);
	obj->cy.body.t = t;
	obj->cy.body.type = 'c';
	obj->cy.body.point = ray_at(ray, t);
	obj->cy.body.color = obj->cy.color;
	obj->cy.body.normal = vec_unit(vec_sub(vec_sub(obj->cy.body.point, \
				obj->cy.bottom_end_cap), vec_mult(obj->cy.normal, m)));
	return (&obj->cy.body);
}

t_intersec	*cylinder_intersect(t_ray ray, t_object *obj)
{
	t_intersec	*body;
	t_intersec	*cap;
	t_intersec	*closest;

	body = cy_body_intersect(ray, obj);
	cap = intersect_cap(ray, obj);
	if (body && cap)
	{
        //closest = compare_distance(body, cap, ray.origin);
		if (body->t <= cap->t)
			return (body);
		return (cap);
	}
    else if (body)
        closest = body;
    else if (cap)
        closest = cap;
    else
        closest = NULL;
    return (closest);
}

/* t_intersec	*cylinder_intersect(t_ray ray, t_object *obj)
{
	t_float	t;
	t_float	m;

	t = find_t_cy(ray, obj);
	if (t == -1.0)
		return (intersect_cap(ray, obj));
	m = vec_dot(ray.direction, obj->cy.normal) * t + \
		vec_dot(vec_sub(ray.origin, obj->cy.bottom_end_cap), obj->cy.normal);
	if (m < EPSILON || m > obj->cy.height)
		return (intersect_cap(ray, obj));
	obj->temp.t = t;
	obj->temp.type = 'c';
	obj->temp.point = ray_at(ray, obj->temp.t);
	obj->temp.color = obj->cy.color;
	obj->temp.normal = vec_unit(vec_sub(vec_sub(obj->temp.point, \
				obj->cy.bottom_end_cap), vec_mult(obj->cy.normal, m)));
	return (&obj->temp);
} */
