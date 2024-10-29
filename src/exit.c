
#include "minirt.h"

void	free_content(t_data *data)
{
	if (data->image)
		mlx_delete_image(data->mlx_ptr, data->image);
	if (data->mlx_ptr)
		mlx_terminate(data->mlx_ptr);
	if (data->scene)
	{
		free(data->scene);
	}
	if (data->lines)
		free_arr(data->lines, NULL);
	free(data);
	data = NULL;
}

void	ft_exit(int exit_code, t_data *data, char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	if (data)
		free_content(data);
	exit(exit_code);
}
