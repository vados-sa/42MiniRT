
#include "minirt.h"

void	free_content(t_data *data)
{
	int	i;

	/* if (data->scene)
	{

	} */
	if (data->lines)
	{
		i = 0;
		while (data->lines[i])
			free(data->lines[i++]);
		free(data->lines);
	}

}

int	ft_return_int(int exit_code, t_data *data, char *message)
{
	if (message)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(message, 2);
	}
	if (data)
	{
		if (data->mlx_ptr)
		{
			mlx_close_window(data->mlx_ptr);
			mlx_terminate(data->mlx_ptr);
		}
		free_content(data);
		free(data);
		data = NULL;
	}
	return (exit_code);
}

void	*ft_return_ptr(t_data *data, char *message)
{
	ft_return_int(1, data, message);
	return (NULL);
}

void	ft_exit(int exit_code, t_data *data, char *message)
{
	ft_return_int(exit_code, data, message);
	exit(exit_code);
}
