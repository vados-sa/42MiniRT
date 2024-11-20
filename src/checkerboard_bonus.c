
#include "minirt.h"

t_coord	planar_map(t_coord plane, t_coord normal)
{
	t_float	u;
	t_float	v;

	if (fabs(normal.y) > EPSILON) //doublecheck this before eval!!
	{
		u = plane.x - floor(plane.x);
		v = plane.z - floor(plane.z);
	}
	else if (fabs(normal.x) > EPSILON) //doublecheck this before eval!!
	{
		u = plane.z - floor(plane.z);
		v = plane.y - floor(plane.y);
	}
	else if (fabs(normal.z) > EPSILON) //doublecheck this before eval!!
	{
		u = plane.x - floor(plane.x);
		v = plane.y - floor(plane.y);
	}
	return (coord(u, v, 0));
}

bool	checker_plane(t_coord point, t_coord normal)
{
	t_coord	uv;

	uv = planar_map(point, normal);
	if (((int)floor(uv.x * 2) % 2) == ((int)floor(uv.y * 2) % 2))
		return (true);
	return (false);
}

/**
 * checkerboard based on the color of the object in the .rt file and
 * on its complementary color
 */
t_color	checkerboard(t_intersec *object)
{
	t_color	black;
	t_color	white; //complementary color

	black = object->color;
	white = col(abs(255 - black.r), abs(255 - black.g), abs(255 - black.b), 255);
	if (object->type == 'p')
	{
		if (checker_plane(object->point, object->normal))
			return (black);
	}
/* 	if (type == 's')
	{
		if (checker_sphere(point))
			return (black);
	}
	if (type == 'c')
	{
		if (checker_cylinder(point))
			return (black);
	} */
	return (white);
}
