
#include "minirt.h"

void	ft_exit(int exit_code, t_data *data, char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	mlx_terminate(data->mlx_ptr);
	if (data)
		free(data);
	return (exit_code);
}
