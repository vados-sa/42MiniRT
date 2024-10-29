
#include "minirt.h"

void	free_content(t_data *data)
{
	int	i;

	if (data->image)
		mlx_delete_image(data->mlx_ptr, data->image);
	if (data->mlx_ptr)
		mlx_terminate(data->mlx_ptr);
	if (data->scene)
	{
		free(data->scene);
	}
	if (data->lines)
	{
		i = 0;
		while (data->lines[i])
			free(data->lines[i++]);
		free(data->lines);
	}
	free(data);
	data = NULL;
}

void	ft_exit(int exit_code, t_data *data, char *message)
{
	if (message)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(message, 2);
	}
	if (data)
		free_content(data);
	exit(exit_code);
}
