
#include "minirt.h"

int	check_color(char *info, t_data *data, char type)
{
	char	**color;
	int		i;
	int		j;
	t_color	rgb;

	if (comma_count(info) != 2)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	color = ft_split(info, ',');
	if (ft_arr_len(color) != 3)
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	rgb = create_color(ft_atoi(info[0]), ft_atoi(info[1]), ft_atoi(info[2]));
	if ((rgb.r < 0 || rgb.r > 255) || (rgb.g < 0 || rgb.g > 255)
		|| (rgb.b < 0 || rgb.b > 255))
		return (ft_putendl_fd(GEN_INFO_ERR, 2), 1);
	if (type == 'A')
		data->scene->a.color = rgb;
	if (type == 'L')
		(light_last_node(data->scene->l))->color = rgb;
	if (type == 's')
		object_last_node(data->scene->objects)->sp->color = rgb; //check later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl->color = rgb;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy->color = rgb;
	return (0);
}

int	check_identifier(char *info, t_data *data, char *type)
{
	if (!ft_strcmp(type, "element") && info [1])
		return (ft_putendl_fd(TYPE_ID_ERR, 2), 1);
	else if (!ft_strcmp(type, "object") && info [2])
		return (ft_putendl_fd(TYPE_ID_ERR, 2), 1);
	return (0);
}

int	float_check(char *info)
{
	int	i;
	int	dot_count;

	if (!ft_isdigit(info[0]))
		return (1);
	i = 0;
	dot_count = 0;
	while (info[++i])
	{
		if (info[i] == '.')
			dot_count++;
		if ((info[i] != '.' && !ft_isdigit(info[i])) || dot_count > 1)
			return (1);
	}
	return (0);
}

int	check_ratio(char *info, t_data *data, char type)
{
	double	ratio;

	if (float_check(info))
		return (ft_putendl_fd(RATIO_ERR, 2), 1);
	ratio = ft_atof(info);
	if (ratio < 0.0 || ratio > 1.0)
		return (ft_putendl_fd(RATIO_ERR, 2), 1);
	if (type == 'A')
		data->scene->a.ratio = ratio;
	else
		(light_last_node(data->scene->l))->brightness = ratio; //check later
	return (0);
}

int	comma_count(char *info)
{
	int	i;
	int	comma_count;

	i = -1;
	comma_count = 0;
	while (info[++i])
	{
		if (!ft_isdigit(info[i]) && info[i] != ',')
			return (1);
		if (info[i] == ',')
			comma_count++;
	}
	return (comma_count);
}
