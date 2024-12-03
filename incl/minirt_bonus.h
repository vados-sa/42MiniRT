
#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "structs.h"
# include "minirt.h"

t_color		checkerboard(t_intersec *object);
void		parse_bonus(t_data *data);
t_intersec	*cone_intersect(t_ray ray, t_object *obj);
void		assign_xyz_bonus(char type, t_data *data, t_coord xyz, \
								char coord_type);
void		assign_rgba_bonus(char type, t_data *data, t_color rgba);




#endif
