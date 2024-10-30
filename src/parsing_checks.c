
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

int	check_color(char *info, t_data *data, char type)
{
	char	**color;
	int		i;
	int		j;
	t_color	rgb;

	color = split_three(info);
	if (!color)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (int_check(color[0]) || int_check(color[1]) || int_check(color[2]))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	rgb = create_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	if ((rgb.r < 0 || rgb.r > 255) || (rgb.g < 0 || rgb.g > 255)
		|| (rgb.b < 0 || rgb.b > 255))
		return (ft_putendl_fd(COL_RANGE_ERR, 2), 1);
	//ft_assign(type, data, rgb);
	if (type == 'A')
		data->scene->a.color = rgb;
	if (type == 'L')
		(light_last_node(data->scene->l))->color = rgb;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.color = rgb; //check later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.color = rgb;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.color = rgb;
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
	double	ratio;

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

t_coordinate	create_coordinates(int x, int y, int z)
{
	t_coordinate	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	return (xyz);
}

int	check_coordinates(char *info, t_data *data, char type)
{
	char			**coordinates;
	int				i;
	int				j;
	t_coordinate	xyz;

	coordinates = split_three(info);
	if (!coordinates)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (float_check(coordinates[0]) || float_check(coordinates[1])
		|| float_check(coordinates[2]))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	xyz = create_coordinates(ft_atof(coordinates[0]), ft_atof(coordinates[1]),
			ft_atof(coordinates[2]));
	if ((xyz.x < -1 || xyz.x > 1) || (xyz.y < -1 || xyz.y > 1)
		|| (xyz.z < -1 || xyz.z > 1))
		return (ft_putendl_fd(COL_RANGE_ERR, 2), 1); // there might have  to be another check for the lenght.
	//ft_assign(type, data, rgb);
	if (type == 'C')
		data->scene->c.normal = xyz;
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.normal = xyz;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.normal = xyz;
	return (0);
}

int	check_normal(char *info, t_data *data, char type)
{
	char			**coordinates;
	int				i;
	int				j;
	t_coordinate	xyz;

	coordinates = split_three(info);
	if (!coordinates)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (float_check(coordinates[0]) || float_check(coordinates[1])
		|| float_check(coordinates[2]))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	xyz = create_coordinates(ft_atof(coordinates[0]), ft_atof(coordinates[1]),
			ft_atof(coordinates[2]));
	//ft_assign(type, data, rgb);
	if (type == 'C')
		data->scene->c.view_point = xyz;
	if (type == 'L')
		(light_last_node(data->scene->l))->point = xyz;
	if (type == 's')
		object_last_node(data->scene->objects)->sp.center = xyz; //check later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl.point = xyz;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy.center = xyz;
	return (0);
}

