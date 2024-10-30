
#include "minirt.h"

int	parse_sp(t_data *data, char *line)
{
	t_object	*sp_node;
	char		**info;

	sp_node = new_object_node();
	if (!sp_node)
		ft_exit(1, data, ALLOC_ERR);
	add_object_node(&data->scene->objects, sp_node);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 4)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "object") || 
		check_coordinates(info[1], data, 's') || check_dimension(info[2]) ||
		check_color(info[3], data, 's'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	return (0);
}
