
#include "../incl/minirt.h"

void	my_keyhook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		//ft_error
		mlx_terminate(data->mlx_ptr);
		free(data);
		exit (0);
	}
}


int main(void)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		perror(ALLOC_ERR);
		return (1);
	}
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!data->mlx_ptr)
		return (1);
		//ft_error();

	//mlx_loop_hook(data->mlx_ptr, ft_hook, data);
	mlx_key_hook(data->mlx_ptr, (mlx_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);

	mlx_terminate(data->mlx_ptr);
	free(data);

	printf("hello world");
	return (0);
}
