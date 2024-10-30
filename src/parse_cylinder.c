
#include "minirt.h"

int	parse_cy(t_data *data, char *line)
{
	t_object	*cy_node;
	char		**info;

	cy_node = new_object_node();
	if (!cy_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, cy_node);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 6)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "object") ||
		check_coordinates(info[1], data, 'c') ||
		check_normal(info[2], data, 'c') || check_dimension(info[3], CY_DIAM, data)
		|| check_dimension(info[4], CY_HEIGHT, data) || check_color(info[5], data, 'c'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	cy_node->type = 'c';
	return (0);
}
