
#include "minirt.h"

t_color	col_mult(t_color c, t_float scalar)
{
	return (col(c.r * scalar, c.g * scalar, c.b * scalar, c.a));
}

/**
 * This function multiplies the color of an object by the
 * ratio and color of the ambient lighting or "global illumination"
 * in the scene.
 * @param color: pointer to the color of the object or background
 * @param ambient: ambietn light struct containing ratio and color
 */
t_color	ambient_light(t_A ambient)
{
    t_color light;

    light = col_mult(ambient.color, ambient.ratio);
	return (light);
 /* color->r *= ((t_float)light.r / 255.0);
    color->g *= ((t_float)light.g / 255.0);
    color->b *= ((t_float)light.b / 255.0);
    color->a = color->a; */
}

/**
 * the larger θ becomes, the less of an impact
 * the light should have on the fragment's color.
 * to get (only) the cosine of the angle between
 * both vectors we will work with unit vectors (vectors of length 1)
 * so we need to make sure all the vectors are normalized
 * surface_normal: a vector that is perpendicular to the vertex' surface.
 * The directed light ray: a direction vector that is the difference vector
 * between the light's position and the fragment's position. To calculate this light
 * ray we need the light's position vector and the fragment's position vector.
 * @param l: a linked list of light sources
 * @param hit_rec: a t_intersection struct that contains the surface normal and the point where the object was hit
 */
t_color	diffuse_light(t_L *l, t_intersec *hit_rec)
{
    t_coord     light_dir;
    t_float     dot_product;
    t_color     diffuse;

	diffuse = col(0, 0, 0, 0);
    while (l)
    {//figure out how to combine multiple lights
        hit_rec->normal = vec_unit(hit_rec->normal); //maybe not needed if normalized before?
        light_dir = vec_unit(vec_sub(l->point, hit_rec->point));
        dot_product = fmax(vec_dot(hit_rec->normal, light_dir), 0.0); //if angle is bigger than 90%, no light
        if (dot_product > 0.0)
        {
            diffuse = col_mult(col_mult(l->color, dot_product), l->brightness);
           /*  hit_rec->color.r *= ((t_float)diffuse.r / 255.0);
            hit_rec->color.g *= ((t_float)diffuse.g / 255.0);
            hit_rec->color.b *= ((t_float)diffuse.b / 255.0);
            hit_rec->color.a = hit_rec->color.a; */
        }
        l = l->next;
    }
	return (diffuse);
}

t_color	calculate_light(t_color obj_color, t_data *data, t_intersec *hit_rec)
{
	t_color	result;
	t_color	ambient;
	t_color	diffuse;

	ambient = ambient_light(data->scene->a);
	diffuse = diffuse_light(data->scene->l, hit_rec);
	result.r =
	result.g =
	result.b =
	result.a =
	return (result);
}
