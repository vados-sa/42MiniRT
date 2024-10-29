
#include "minirt.h"

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
			return(1);
	}
	return (0);
}

t_object	*new_object_node(void)
{
	t_object	*new;

	new = (t_object *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	add_object_node(t_object **light, t_object	*new)
{
	t_object	*tmp;

	if (light)
	{
		if (!*light)
			*light = new;
		else
		{
			tmp = object_last_node(*light);
			tmp->next = new;
		}
	}
}

t_object	*object_last_node(t_object *head)
{
	t_object	*trav;

	if (!head)
		return (NULL);
	trav = head;
	while (trav->next)
		trav = trav->next;
	return (trav);
}

t_L	*new_light_node(void)
{
	t_L	*new;

	new = (t_L *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_L	*light_last_node(t_L *light)
{
	t_L	*trav;

	if (!light)
		return (NULL);
	trav = light;
	while (trav->next)
		trav = trav->next;
	return (trav);
}

void	add_light_node(t_L **light, t_L	*new)
{
	t_L	*tmp;

	if (light)
	{
		if (!*light)
			*light = new;
		else
		{
			tmp = light_last_node(*light);
			tmp->next = new;
		}
	}
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

t_color	create_color(int r, int g, int b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

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
		object_last_node(data->scene->objects)->sp->color = rgb; //ccheck later
	if (type == 'p')
		object_last_node(data->scene->objects)->pl->color = rgb;
	if (type == 'c')
		object_last_node(data->scene->objects)->cy->color = rgb;
	return (0);
}

int	parse_a(t_data *data, char *line)
{
	char	**info;
	int		i;

	if (line[ft_strlen(line)] == ' ')
		ft_exit(1, data, SPACE_ERR);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 3)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "element") 
		|| check_ratio(info[1], data, 'A') || check_colors(info[2], data, 'A'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	return (1);
}

void	parse_lines(t_data *data)
{
	static int	qnt_a;
	static int	qnt_c;
	static int	qnt_l;
	int			i;

	i = -1;
	while (data->lines[++i])
	{
		if (data->lines[i][0] == 'A' && qnt_a < 1)
			qnt_a += parse_a(data, data->lines[i]);
		else if (data->lines[i][0] == 'C' && qnt_c < 1)
			qnt_c += parse_c(data);
		else if (data->lines[i][0] == 'L' && qnt_l < 1)
			qnt_l += parse_l(data);
		else if (ft_strncmp(data->lines[i], "pl", 2) == 0)
			parse_pl(data);
		else if (ft_strncmp(data->lines[i], "sp", 2) == 0)
			parse_sp(data);
		else if (ft_strncmp(data->lines[i], "cy", 2) == 0)
			parse_cy(data);
		else
			ft_exit(1, data, TYPE_ID_ERR);
	}
}

void	parse(t_data *data, char *filename)
{
	read_file(filename, data);
	//parse_lines(data);
}
