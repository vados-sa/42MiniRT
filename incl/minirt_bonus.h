
#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "minirt.h"

t_color		checkerboard(t_intersec *object);
t_intersec	*cone_intersect(t_ray ray, t_object *obj);

typedef struct s_cone
{
	t_coord		center;
	t_coord		axis;
	t_float		radius;
	t_float		height;
	t_color		color;
	t_coord		vertex;
	t_coord		cap_center;
	t_coord		cap_normal;
}	t_cone;

#endif
