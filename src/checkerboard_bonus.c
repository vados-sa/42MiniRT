
#include "minirt.h"

t_coord	planar_map(t_coord plane)
{
	t_float	u;
	t_float	v;
	double	int_part;

	int_part = 1.0;
	u = fabs(modf(plane.x, &int_part));
	v = fabs(modf(plane.z, &int_part));

	return (coord(u, v, 0));
}

bool	checker_plane(t_coord point)
{
	t_coord	uv;

	uv = planar_map(point);
	if ((uv.x + uv.y) < 0.5 || (uv.x + uv.y) > 1.0)
		return (true);
	return (false);
}

/**
 * checkerboard based on the color of the object in the .rt file and
 * on its complementary color
 */
t_color	checkerboard(t_color black, char type, t_coord point)
{
	t_color	white; //complementary color

	white = col(abs(255 - black.r), abs(255 - black.g), abs(255 - black.b), 255);
	if (type == 'p')
	{
		if (checker_plane(point))
			return (black);
	}
	return (white);
}
