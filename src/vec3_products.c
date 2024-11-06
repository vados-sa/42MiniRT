
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

	/* if we have problems with -0 coordinates
    // If the value is very close to zero, set it to exactly zero to avoid -0
    if (fabs(product.x) < 1e-8) product.x = 0.0;
    if (fabs(product.y) < 1e-8) product.y = 0.0;
    if (fabs(product.z) < 1e-8) product.z = 0.0; */

	return (product);
}
