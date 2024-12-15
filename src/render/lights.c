/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:23 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/15 17:52:04 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: calculates the color of the object taking into
 * account the spotlights in the .rt file.
 * @details: The larger the dot product becomes, the less of an impact
 * the light should have on the object's color.
 * To get just(!!!) the cosine of the angle between both vectors
 * we will work with the following unit(!!!) vectors:
 * surface_normal: a vector perpendicular to the object's surface
 * the direction of the light ray: the difference vector
 * between the light's position and the object's position.
 * a · b = |a| × |b| × cos(θ), so if the length of both a and b are 1,
 * we should get cos(θ).
 * To avoid rounding problems and strange surface colors,
 * we compare to our arbitrary EPSILON.
 * @param l: a linked list of light sources
 * @param hit_rec: a t_intersection struct with the color,
 * the surface normal and the intersection point
 */
t_color	diffuse_light(t_l *l, t_intersec *hit_rec, t_data *data)
{
	t_ray	light;
	t_float	dot_product;
	t_color	diffuse;
	t_color	temp_diffuse;
	bool	shadow;

	diffuse = col(0, 0, 0, 0);
	while (l != NULL && hit_rec)
	{
		light.direction = vec_unit(vec_sub(l->point, hit_rec->point));
		light.origin = l->point;
		dot_product = fmax(vec_dot(hit_rec->normal, light.direction), EPSILON);
		shadow = check_shadow(light, hit_rec->point, data, hit_rec->normal);
		if (dot_product > EPSILON && shadow == false)
		{
			temp_diffuse = \
				col_mult(col_mult(l->color, dot_product), l->brightness);
			diffuse = col_add(diffuse, temp_diffuse);
		}
		l = l->next;
	}
	return (diffuse);
}

/**
 * @brief: calculates the specular light reflection 
 * based on the light direction, the viewing direction and the reflection vector.
 * The strength determines how concenrtrated the spot reflection becomes 
 * and the strength determines the brightness of it.
 */
t_color specular_light(t_l *light, t_intersec *hit_rec, t_data *data)
{
    t_specular	specular;
	t_color result;
	
    specular.shine = 10.0;
    specular.strength = 0.5;
	result = col(0, 0, 0, 255);
	specular.view_dir = vec_unit(vec_sub(data->scene->c.center, hit_rec->point));
	while(light)
	{
		specular.light_dir = vec_unit(vec_sub(light->point, hit_rec->point));
		specular.reflect_dir = vec_reflect(vec_mult(specular.light_dir, -1.0), hit_rec->normal);
		specular.spec = pow(fmax(vec_dot(specular.view_dir, specular.reflect_dir), 0.0), specular.shine);
		specular.temp_specular = col_mult(light->color, specular.spec * specular.strength);
		result = col_add(result, specular.temp_specular);
		light = light->next;
	}
    return (result);
}

/**
 * @brief: multiplies the color of the object (0-255) by the values of
 * the ambient and diffuse lighting (0-1).
 * The max value for the result r,g,b,a is 255.
 * @param color: color of the intersected object.
 * @returns the final color.
 */
t_color	calculate_light(t_data *data, t_intersec *hit_rec, t_color color)
{
	t_color	result;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	ambient = col_mult(data->scene->a.color, data->scene->a.ratio);
	diffuse = diffuse_light(data->scene->l, hit_rec, data);
	specular = specular_light(data->scene->l, hit_rec, data);
	result.r = ((t_float)(ambient.r + diffuse.r + specular.r) / 255.0) * color.r;
	result.g = ((t_float)(ambient.g + diffuse.g + specular.g) / 255.0) * color.g;
	result.b = ((t_float)(ambient.b + diffuse.b + specular.b) / 255.0) * color.b;
	if (result.r > 255.0)
		result.r = 255.0;
	if (result.g > 255.0)
		result.g = 255.0;
	if (result.b > 255.0)
		result.b = 255.0;
	result.a = 255;
	return (result);
}

/**
 * @brief: checks if a point is lit or in shadow.
 * @details:
 * As opposed to real life, the calculations consider the light ray
 * to go from the object to the light source and not versa.
 * We loop through each object in our list.
 * If the ray encounters an object before it gets to the light point,
 * it @returns true, otherwise it @returns false.
 * To avoid "self-shadowing", we start not directly at
 * the object-light intersection point, but slightly further,
 * we use EPSILON to do this.
 * @param point: the intersection point of the light and the object
 * @param normal: surface normal of the intersected object
 */
bool	check_shadow(t_ray light, t_coord point, t_data *data, t_coord normal)
{
	t_intersec	*shadow_hit;
	t_object	*object;
	t_ray		shadow_ray;
	t_float		max_len;

	shadow_ray.direction = light.direction;
	shadow_ray.origin = vec_add(point, \
		vec_mult(normal, EPSILON));
	object = data->scene->objects;
	max_len = vec_len(vec_sub(light.origin, shadow_ray.origin));
	while (object)
	{
		shadow_hit = NULL;
		shadow_hit = obj_intersection(data, shadow_ray, object);
		if (shadow_hit && shadow_hit->t > EPSILON
			&& shadow_hit->t < max_len - EPSILON)
			return (true);
		object = object->next;
	}
	return (false);
}
