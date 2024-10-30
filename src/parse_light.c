
#include "minirt.h"

int	parse_l(t_data *data, char *line)
{
	char	**info;
	int		i;
	t_L		*node;

	node = new_light_node();
	if (!node)
		ft_exit(1, data, ALLOC_ERR);
	add_light_node(&data->scene->l, node);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 4)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "element")
		|| check_coordinates(info[1], data, 'L')
		|| check_ratio(info[2], data, 'L')
		|| check_color(info[3], data, 'L'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	return (1);
}
