
#include "minirt.h"

char	**split_three(char *info)
{
	int		i;
	int		comma_count;
	char	**str_arr;

	i = -1;
	comma_count = 0;
	while (info[++i])
	{
		if (info[i] == ',')
			comma_count++;
	}
	if (comma_count != 2)
		return (NULL);
	str_arr = ft_split(info, ',');
	if (ft_arr_len(str_arr) != 3)
		return (NULL);
	return (str_arr);
}

void	assign_rgba(char type, t_data *data, t_color rgba)
{
	if (type == 'A')
		data->scene->a.color = rgba;
	if (type == 'L')
		(light_last_node(data->scene->l))->color = rgba;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.color = rgba; //check later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.color = rgba;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.color = rgba;
}

int	check_color(char *info, t_data *data, char type)
{
	char	**color;
	int		i;
	int		j;
	t_color	rgba;

	color = split_three(info);
	if (!color)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (int_check(color[0]) || int_check(color[1]) || int_check(color[2]))
	{
		free_arr(color, NULL);
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	}
	rgba = col(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]), 255);
	free_arr(color, NULL);
	if ((rgba.r < 0 || rgba.r > 255) || (rgba.g < 0 || rgba.g > 255)
		|| (rgba.b < 0 || rgba.b > 255))
		return (ft_putendl_fd(COL_RANGE_ERR, 2), 1);
	assign_rgba(type, data, rgba);
	/* if (type == 'A')
		data->scene->a.color = rgba;
	if (type == 'L')
		(light_last_node(data->scene->l))->color = rgba;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.color = rgba; //check later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.color = rgba;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.color = rgba; */
	return (0);
}

int	check_identifier(char *info, t_data *data, char *type)
{
	if (!ft_strcmp(type, "element") && info[1])
		return (ft_putendl_fd(TYPE_ID_ERR, 2), 1);
	else if (!ft_strcmp(type, "object") && info[2])
		return (ft_putendl_fd(TYPE_ID_ERR, 2), 1);
	return (0);
}

int	check_ratio(char *info, t_data *data, char type)
{
	t_float	ratio;

	if (float_check(info))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	ratio = ft_atof(info);
	if (ratio < 0.0 || ratio > 1.0)
		return (ft_putendl_fd(RATIO_ERR, 2), 1);
	if (type == 'A')
		data->scene->a.ratio = ratio;
	else
		(light_last_node(data->scene->l))->brightness = ratio; //check later
	return (0);
}

t_coord	coord(t_float x, t_float y, t_float z)
{
	t_coord	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	return (xyz);
}

void	assign_xyz(char type, t_data *data, t_coord xyz, char coord_type)
{
	if (coord_type == 'n')
	{
		if (type == 'C')
		data->scene->c.orientation = vec_unit(xyz);
		if (type == 'p')
			object_last_node(data->scene->objects)->pl.normal = vec_unit(xyz);
		if (type == 'c')
			object_last_node(data->scene->objects)->cy.normal = vec_unit(xyz);
	}
	else if (coord_type == 'c')
	{
		if (type == 'C')
			data->scene->c.center = xyz;
		if (type == 'L')
			(light_last_node(data->scene->l))->point = xyz;
		if (type == 's')
			object_last_node(data->scene->objects)->sp.center = xyz; //check later
		if (type == 'p')
			object_last_node(data->scene->objects)->pl.point = xyz;
		if (type == 'c')
			object_last_node(data->scene->objects)->cy.center = xyz;
	}
}

int	check_normal(char *info, t_data *data, char type)
{
	char			**coordinates;
	int				i;
	int				j;
	t_coord	xyz;

	coordinates = split_three(info);
	if (!coordinates)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (float_check(coordinates[0]) || float_check(coordinates[1])
		|| float_check(coordinates[2]))
	{
		free_arr(coordinates, NULL);
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	}
	xyz = coord(ft_atof(coordinates[0]), ft_atof(coordinates[1]),
			ft_atof(coordinates[2]));
	free_arr(coordinates, NULL);
	if (vec_len(xyz) > (1.0 + EPSILON) || vec_len(xyz) < (1.0 - EPSILON))
		return (ft_putendl_fd(NORMAL_RANGE_ERR, 2), 1);
	//if ((xyz.x < -1.0 || xyz.x > 1.0) || (xyz.y < -1.0 || xyz.y > 1.0)
	//	|| (xyz.z < -1.0 || xyz.z > 1.0))
	assign_xyz(type, data, xyz, 'n');
	/* if (type == 'C')
		data->scene->c.orientation = xyz;
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.normal = vec_unit(xyz);
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.normal = vec_unit(xyz); */
	return (0);
}

int	check_coordinates(char *info, t_data *data, char type)
{
	char			**coordinates;
	int				i;
	int				j;
	t_coord			xyz;

	coordinates = split_three(info);
	if (!coordinates)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (float_check(coordinates[0]) || float_check(coordinates[1])
		|| float_check(coordinates[2]))
	{
		free_arr(coordinates, NULL);
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	}
	xyz = coord(ft_atof(coordinates[0]), ft_atof(coordinates[1]),
			ft_atof(coordinates[2]));
	free_arr(coordinates, NULL);
	assign_xyz(type, data, xyz, 'c');
	/* if (type == 'C')
		data->scene->c.center = xyz;
	if (type == 'L')
		(light_last_node(data->scene->l))->point = xyz;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.center = xyz; //check later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.point = xyz;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.center = xyz; */
	return (0);
}

int	check_dimension(char *line, t_dimension type, t_data *data)
{
	t_float	dimension;

	if (float_check(line))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	dimension = ft_atof(line);
	if (dimension <= 0.0)
		return (ft_putendl_fd(DIMENSION_ERR, 2), 1);
	if (type == CY_DIAM)
		object_last_node(data->scene->objects)->cy.radius = dimension / 2.0;
	if (type == CY_HEIGHT)
		object_last_node(data->scene->objects)->cy.height = dimension;
	if (type == SP_DIAM)
		object_last_node(data->scene->objects)->sp.radius = dimension / 2.0;
	return (0);
}
