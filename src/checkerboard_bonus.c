
#include "minirt.h"

t_coord	planar_map(t_coord plane)
{
	t_float	u;
	t_float	v;

	u = modf(plane.x, 1);
	v = modf(plane.z, 1);

	return (coord(u, v, 0));
}

uv_checkers()
{
	planar_map = planar_map(point);
}

/**
 * checkerboard based on the color of the object in the .rt file and
 * on its complementary color
 */
checkerboard(t_color black, char type, t_coord point)
{
	t_color	white; //complementary color

	white = col(abs(255 - black.r), abs(255 - black.g), abs(255 - black.b), 255);
	if (type == 'p')
		checker_plane(point, black, white);
}
