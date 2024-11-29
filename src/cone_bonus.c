
#include "minirt.h"
# include "bonus.h"
# include "structs.h"

// initialize cone structure --> see best way to do that
// parse cone scene (similar to cylinder)
// render cone
// put cap

// change calculation of 'c' accordingly.
static t_float	find_discriminant_cone(t_ray ray, t_object *obj, t_float a, \
t_float b)
{
	t_float	c;

	// c   = X|X - (1+k*k)*(X|V)^2
	c = vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), vec_sub(ray.origin, \
		obj->cy.top_end_cap)) - vec_dot(vec_sub(ray.origin, \
		obj->cy.top_end_cap), obj->cy.normal) * \
		vec_dot(vec_sub(ray.origin, obj->cy.top_end_cap), \
		obj->cy.normal) - obj->cy.radius * obj->cy.radius;
	return (b * b - 4 * a * c);
}

// change calculation of 'a' and 'b' accordingly.
static t_float	find_t_cone(t_ray ray, t_object *obj)
{
	t_float	discriminant;
	t_float	a;
	t_float	b;
	t_float	t_max;
	t_float	t_min;

	// a   = D|D - (1+k*k)*(D|V)^2
	a = vec_dot(ray.direction, ray.direction) - vec_dot(ray.direction, \
		obj->cy.normal) * vec_dot(ray.direction, obj->cy.normal);
	// b/2 = D|X - (1+k*k)*(D|V)*(X|V)
	b = 2 * (vec_dot(ray.direction, vec_sub(ray.origin, obj->cy.top_end_cap)) - \
		vec_dot(ray.direction, obj->cy.normal) * vec_dot(vec_sub(ray.origin, \
		obj->cy.top_end_cap), obj->cy.normal));
	discriminant = find_discriminant(ray, obj, a, b);
	if (discriminant < 0)
		return (-1);
	t_min = ((-b - sqrt(discriminant))) / (2.0 * a);
	t_max = ((-b + sqrt(discriminant))) / (2.0 * a);
	if (t_min > t_max && t_min > 0)
		return (t_max);
	else if (t_min > 0)
		return (t_min);
	else if (t_max >= 0)
		return (t_max);
	else
		return (-1);
}

t_intersec	*cone_intersect(t_ray ray, t_object *obj)
{
	t_float	t;
	t_float	m;

	t = find_t_cone(ray, obj);
	if (t == -1)
		return (NULL);
	m = vec_dot(ray.direction, obj->cone.axis) * t + \
		vec_dot(vec_sub(ray.origin, obj->cone.vertex), obj->cone.axis); 
	if (m < 0 || m > obj->cy.height)
		return (intersect_cone_cap(ray, obj, t)); // create function
	obj->temp.t = t;
	obj->temp.point = ray_at(ray, obj->temp.t);
	obj->temp.color = obj->cone.color;
	obj->temp.normal = vec_unit(vec_sub(vec_sub(obj->temp.point, \
				obj->cy.top_end_cap), vec_mult(obj->cone.axis, m)));
}

/* int	parse_cone(t_data *data, char *line)
{
	t_object	*cone_node;
	char		**info;

	cone_node = new_object_node();
	if (!cone_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, cone_node);
	info = split_check(line, data);
	if (check_identifier(info[0], data, "object")
		|| check_coordinates(info[1], data, 'c')
		|| check_normal(info[2], data, 'c')
		|| check_dimension(info[3], CY_DIAM, data)
		|| check_dimension(info[4], CY_HEIGHT, data)
		|| check_color(info[5], data, 'c'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	populate_cone_node(cone_node);
	return (0);
} */
