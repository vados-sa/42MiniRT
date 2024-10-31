
#include "minirt.h"

t_color	col(int r, int g, int b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
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
