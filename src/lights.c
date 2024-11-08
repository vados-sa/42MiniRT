
#include "minirt.h"

t_color	col_mult(t_color c, t_float scalar)
{
	return (col(c.r * scalar, c.g * scalar, c.b * scalar, c.a));
}

void    ambient_light(t_A ambient, t_color *color)
{
    t_color light;

    light = col_mult(ambient.color, ambient.ratio);
    color->r = color->r * ((t_float)light.r / 255.0);
    color->g = color->g * ((t_float)light.g / 255.0);
    color->b = color->b * ((t_float)light.b / 255.0);
    color->a = color->a;
}