/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:27 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 16:05:26 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: compares to intersection points to determine the closest.
 */
t_intersec	*compare_distance(t_intersec *obj_1, t_intersec *obj_2, \
								t_coord origin)
{
	t_float	d1;
	t_float	d2;

	if (!obj_2)
		return (obj_1);
	if (!obj_1)
		return (obj_2);
	d1 = vec_len(vec_sub(obj_1->point, origin));
	d2 = vec_len(vec_sub(obj_2->point, origin));
	if (d1 <= d2)
		return (obj_1);
	else
		return (obj_2);
}

/**
 * @brief: function looping through each object, checking for 
 * intersections of the ray and the objects and comparing 
 * the intersections to find the closest one.
 * @returns the closest t_intersect struct or NULL if there is none.
 */
t_intersec	*intersection(t_data *data, t_ray ray)
{
	t_object	*object;
	t_intersec	*closest;
	t_intersec	*temp;

	object = data->scene->objects;
	closest = NULL;
	while (object)
	{
		temp = NULL;
		temp = obj_intersection(data, ray, object);
		closest = compare_distance(temp, closest, ray.origin);
		object = object->next;
	}
	if (closest)
		return (closest);
	return (NULL);
}

t_intersec	*obj_intersection(t_data *data, t_ray ray, t_object *object)
{
	t_intersec	*hit_rec;

	if (object->type == 's')
		hit_rec = sphere_intersect(data, ray, object);
	else if (object->type == 'p')
		hit_rec = plane_intersect(ray, object);
	else if (object->type == 'c')
		hit_rec = cylinder_intersect(ray, object);
	if (hit_rec)
		hit_rec->self = object;
	return (hit_rec);
}
