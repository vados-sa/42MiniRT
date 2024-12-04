/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:46:21 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/04 14:46:27 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float	vec_dot(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_coord	vec_cross(t_coord v1, t_coord v2)
{
	t_coord	product;

	product.x = v1.y * v2.z - v1.z * v2.y;
	product.y = v1.z * v2.x - v1.x * v2.z;
	product.z = v1.x * v2.y - v1.y * v2.x;
	return (product);
}

t_color	col_mult(t_color c, t_float scalar)
{
	return (col(c.r * scalar, c.g * scalar, c.b * scalar, c.a));
}

t_color	col_add(t_color c1, t_color c2)
{
	return (col(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a));
}
