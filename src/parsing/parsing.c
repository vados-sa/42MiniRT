
#include "minirt.h"

t_color	col(int r, int g, int b, int a)
{
	t_color	rgba;

	rgba.r = r;
	rgba.g = g;
	rgba.b = b;
	rgba.a = a;
	return (rgba);
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
		else if (data->lines[i][0] == 'L' && qnt_l < MAX_LIGHT)
			qnt_l += parse_l(data, data->lines[i]);
		else if (ft_strncmp(data->lines[i], "pl", 2) == 0)
			parse_pl(data, data->lines[i]);
		else if (ft_strncmp(data->lines[i], "sp", 2) == 0)
			parse_sp(data, data->lines[i]);
		else if (ft_strncmp(data->lines[i], "cy", 2) == 0)
			parse_cy(data, data->lines[i]);
		else if (data->bonus == 1 && ft_strncmp(data->lines[i], "co", 2))
			ft_exit(1, data, TYPE_ID_ERR);
	}
}

void	parse(t_data *data, char *filename)
{
	read_file(filename, data);
	if (data->bonus == 1)
		parse_bonus(data);
	parse_lines(data);
}
