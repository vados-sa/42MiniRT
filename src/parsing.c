
#include "minirt.h"

t_color	create_color(int r, int g, int b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
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
		|| check_ratio(info[1], data, 'A') || check_color(info[2], data, 'A'))
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
		if (data->lines[i][0] == '#')
			continue ;
		if (data->lines[i][0] == 'A' && qnt_a < 1)
			qnt_a += parse_a(data, data->lines[i]);
		else if (data->lines[i][0] == 'C' && qnt_c < 1)
			qnt_c += parse_c(data, data->lines[i]);
		else if (data->lines[i][0] == 'L' && qnt_l < 1)
			qnt_l += parse_l(data, data->lines[i]);
		else if (ft_strncmp(data->lines[i], "pl", 2) == 0)
			parse_pl(data, data->lines[i]);
		else if (ft_strncmp(data->lines[i], "sp", 2) == 0)
			parse_sp(data, data->lines[i]);
		else if (ft_strncmp(data->lines[i], "cy", 2) == 0)
			parse_cy(data, data->lines[i]);
		else
			ft_exit(1, data, TYPE_ID_ERR);
	}
}

void	parse(t_data *data, char *filename)
{
	read_file(filename, data);
	parse_lines(data);
}
