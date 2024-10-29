
#include "minirt.h"

void	parse_lines(t_data *data)
{
	static int	qnt_a;
	static int	qnt_c;
	static int	qnt_l;
	int			i;

	i = -1;
	while (data->lines[++i])
	{
		if (data->lines[i][0] == 'A')
			qnt_a += parse_a(data);
		else if (data->lines[i][0] == 'C')
			qnt_c += parse_c(data);
		else if (data->lines[i][0] == 'L')
			qnt_l += parse_l(data);
		else if (ft_strncmp(data->lines[i], "pl", 2) == 0)
			parse_pl(data);
		else if (ft_strncmp(data->lines[i], "sp", 2) == 0)
			parse_sp(data);
		else if (ft_strncmp(data->lines[i], "cy", 2) == 0)
			parse_cy(data);
		else
			ft_exit(1, data, INVALID_ERR);
	}
	if (qnt_a > 1 || qnt_c > 1 || qnt_l > 1)
		ft_exit(1, data, QNT_ERR);
}

void	parse(t_data *data, char *filename)
{
	read_file(filename, data);
	parse_lines(data);
}
