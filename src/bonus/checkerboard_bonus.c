
#include "minirt_bonus.h"

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

t_coord	spherical_map(t_coord point, t_float radius, t_coord normal)
{
	t_float	u;
	t_float	v;
	t_float	theta;
	t_float	phi;

	//if (fabs(normal.y) > EPSILON)
	//{
		theta = atan2(point.x, point.z);
		phi = acos(point.y / radius);
	//}
	//else if (fabs(normal.x) > EPSILON)
	//{
	//	theta = atan2(point.y, point.z);
	//	phi = acos(point.x / radius);
	//}
	//else if (fabs(normal.z) > EPSILON)
	//{
	//	theta = atan2(point.x, point.y);
	//	phi = acos(point.z / radius);
	//}
	u = theta / (2.0 * PI);
	u = 1.0 - (u + 0.5);
	v = 1 - phi / PI;
	u *= 10;
	v *= 10;

	return (coord(u, v, 0));
}

bool	checker_color(t_intersec *object)
{
	t_coord	uv;

	if (object->type == 'p')
		uv = planar_map(object->point, object->normal);
	else if (object->type == 's')
		uv = spherical_map(object->point, object->self->sp.radius, object->normal);
	else
		return (false);
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
	t_color	white;

	black = object->color;
	white = col(abs(255 - black.r), abs(255 - black.g), \
				abs(255 - black.b), 255);
	if (checker_color(object))
		return (black);
	return (white);
}
