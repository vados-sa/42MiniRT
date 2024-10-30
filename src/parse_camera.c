
#include "minirt.h"

int	check_fov(char *info, t_data *data)
{
	double	fov;

	if (float_check(info))
		return (ft_putendl_fd(NUM_ERR, 2), 1);
	fov = ft_atof(info);
	if (fov < 0.0 || fov > 180.0)
		return (ft_putendl_fd(FOV_ERR, 2), 1);
	data->scene->c.fov = fov;
	return (0);
}

int	parse_c(t_data *data, char *line)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 4)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "element")
		|| check_coordinates(info[1], data, 'C')
		|| check_normal(info[2], data, 'C')
		|| check_fov(info[3], data))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	return (1);
}
