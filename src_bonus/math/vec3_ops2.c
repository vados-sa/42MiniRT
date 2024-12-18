/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:46:21 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:58:27 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: calculates the dot product of two vectors.
 * @details: if both v1 and v2 have a length of 1,
 * meaning that they are normalized, we get following values
 * for cos(θ), i.e. the cosine of the angle between the vectors:
 * - 1 if the point in the same direction and are parallel
 * - -1 if they point in the opposite direction and are parallel
 * - 0 if they are perpendicular to each other
 */
t_float	vec_dot(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * @brief: calculates the cross product of two vectors.
 * @details: is denoted as v1 x v2.
 * @returns a vector perpendicular to both parameters.
 * The cross product of parallel vectors is a zero vector.
 */
t_coord	vec_cross(t_coord v1, t_coord v2)
{
	t_coord	product;

	product.x = v1.y * v2.z - v1.z * v2.y;
	product.y = v1.z * v2.x - v1.x * v2.z;
	product.z = v1.x * v2.y - v1.y * v2.x;
	return (product);
}

/**
 * @brief: this function changes the intensity of a color,
 * making it brighter or darker.
 */
t_color	col_mult(t_color c, t_float scalar)
{
	return (col(c.r * scalar, c.g * scalar, c.b * scalar, c.a));
}

t_color	col_add(t_color c1, t_color c2)
{
	return (col(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a));
}
