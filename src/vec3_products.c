
#include "minirt.h"

double	vec_dot(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_coord	vec_cross(t_coord v1, t_coord v2)
{
	t_coord	product;

	product.x = v1.y * v2.z - v1.z * v1.y;
	product.y = v1.z * v2.x - v1.x * v2.z;
	product.z = v1.x * v2.y - v1.y * v2.x;

	return (product);
}
