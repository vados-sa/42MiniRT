
//#include "minirt.h"
#include "minirt_bonus.h"
//# include "structs.h"

// c   = X|X - (1+k*k)*(X|V)^2
static t_float	find_discriminant_cone(t_ray ray, t_object *obj, t_float a, \
t_float b)
{
	t_float	c;

	c = vec_dot(vec_sub(ray.origin, obj->co.vertex), vec_sub(ray.origin, \
		obj->co.vertex)) - (1 + ((obj->co.r / obj->co.h) * \
		(obj->co.r / obj->co.h))) * vec_dot(vec_sub(ray.origin, \
		obj->co.vertex), obj->co.axis) * \
		vec_dot(vec_sub(ray.origin, obj->co.vertex), \
		obj->co.axis);
	return (b * b - 4 * a * c);
}

// a   = D|D - (1+k*k)*(D|V)^2
// b/2 = D|X - (1+k*k)*(D|V)*(X|V)
static t_float	find_t_cone(t_ray ray, t_object *obj)
{
	t_float	discriminant;
	t_float	a;
	t_float	b;
	t_float	t_max;
	t_float	t_min;

	a = vec_dot(ray.direction, ray.direction) - \
	(1 + ((obj->co.r / obj->co.h) * (obj->co.r / obj->co.h))) * \
	vec_dot(ray.direction, obj->co.axis) * vec_dot(ray.direction, obj->co.axis);
	b = 2 * (vec_dot(ray.direction, vec_sub(ray.origin, obj->co.vertex)) - \
	(1 + ((obj->co.r / obj->co.h) * (obj->co.r / obj->co.h))) * \
	vec_dot(ray.direction, obj->co.axis) * vec_dot(vec_sub(ray.origin, \
	obj->co.vertex), obj->co.axis));
	discriminant = find_discriminant_cone(ray, obj, a, b);
	if (discriminant < 0)
		return (-1);
	t_min = ((-b - sqrt(discriminant))) / (2.0 * a);
	t_max = ((-b + sqrt(discriminant))) / (2.0 * a);
	if (t_min > t_max && t_min > 0) // put into a function analyse t_value
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
	m = vec_dot(ray.direction, obj->co.axis) * t + \
		vec_dot(vec_sub(ray.origin, obj->co.vertex), obj->co.axis); 
	if (m < 0 || m > obj->co.h)
		return (NULL); //(intersect_cone_cap(ray, obj, t)); // create function
	obj->temp.t = t;
	obj->temp.point = ray_at(ray, obj->temp.t);
	obj->temp.color = obj->co.color;
	obj->temp.normal = vec_unit(vec_sub(vec_sub(obj->temp.point, \
				obj->co.vertex), vec_mult(vec_mult(obj->co.axis, m), \
				(1 + ((obj->co.r / obj->co.h) * (obj->co.r / obj->co.h))))));
	return (&obj->temp);
}

void	assign_xyz_bonus(char type, t_data *data, t_coord xyz, char coord_type)
{
	if (coord_type == 'n')
	{
		if (type == 'b')
			object_last_node(data->scene->objects)->co.axis = vec_unit(xyz);
	}
	else if (coord_type == 'c')
	{
		if (type == 'b')
			object_last_node(data->scene->objects)->co.center = xyz;
	}
}

void	assign_rgba_bonus(char type, t_data *data, t_color rgba)
{
	if (type == 'b')
		object_last_node(data->scene->objects)->co.color = rgba;
}

static void	populate_cone_node(t_object *node)
{
	node->type = 'b';
	node->co.vertex = vec_sub(node->co.center, \
						vec_mult(node->co.axis, node->co.h / 2));
}

int	parse_cone(t_data *data, char *line)
{
	t_object	*cone_node;
	char		**info;

	cone_node = new_object_node();
	if (!cone_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, cone_node);
	info = split_check(line, data);
	if (check_identifier(info[0], data, "object")
		|| check_coordinates(info[1], data, 'b')
		|| check_normal(info[2], data, 'b')
		|| check_dimension(info[3], CO_DIAM, data)
		|| check_dimension(info[4], CO_HEIGHT, data)
		|| check_color(info[5], data, 'b'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	free_arr(info, NULL);
	populate_cone_node(cone_node);
	return (0);
}

void	parse_bonus(t_data *data)
{
	int			i;

	i = -1;
	while (data->lines[++i])
	{
		if (ft_strncmp(data->lines[i], "co", 2) == 0)
			parse_cone(data, data->lines[i]);
		else
			continue ;
	}
}
