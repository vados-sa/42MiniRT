
#include "minirt.h"

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
t_color	diffuse_light(t_l *l, t_intersec *hit_rec, t_data *data)
{
	t_ray	light;
	t_float	dot_product;
	t_color	diffuse;
	t_color	temp_diffuse;
	bool	shadow;

	diffuse = col(0, 0, 0, 0);
	while (l && hit_rec)
	{
		light.direction = vec_unit(vec_sub(l->point, hit_rec->point));
		light.origin = l->point;
		dot_product = fmax(vec_dot(hit_rec->normal, light.direction), EPSILON);
		shadow = check_shadow(light, hit_rec->point, data);
		if (dot_product > EPSILON && shadow == false)
		{
			temp_diffuse = \
				col_mult(col_mult(l->color, dot_product), l->brightness);
			diffuse = col_add(diffuse, temp_diffuse);
		}
		l = l->next;
	}
	return (diffuse);
}

t_color	calculate_light(t_data *data, t_intersec *hit_rec, t_color color)
{
	t_color	result;
	t_color	ambient;
	t_color	diffuse;

	ambient = col_mult(data->scene->a.color, data->scene->a.ratio);
	diffuse = diffuse_light(data->scene->l, hit_rec, data);
	result.r = ((t_float)(ambient.r + diffuse.r) / 255.0) * color.r;
	result.g = ((t_float)(ambient.g + diffuse.g) / 255.0) * color.g;
	result.b = ((t_float)(ambient.b + diffuse.b) / 255.0) * color.b;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	result.a = 255;
	return (result);
}

bool	check_shadow(t_ray light, t_coord hit_rec_point, t_data *data)
{
	t_intersec	*shadow_hit;
	t_object	*object;
	t_ray		shadow_ray;
	t_float		max_len;

	shadow_ray.direction = light.direction;
	shadow_ray.origin = hit_rec_point;
	object = data->scene->objects;
	max_len = vec_len(vec_sub(light.origin, shadow_ray.origin));
	while (object)
	{
		shadow_hit = NULL;
		shadow_hit = obj_intersection(data, shadow_ray, object);
		object = object->next;
		if (shadow_hit && shadow_hit->t > EPSILON && shadow_hit->t < max_len)
			return (true);
	}
	return (false);
}
