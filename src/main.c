
#include "minirt.h"

void	my_keyhook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_exit(0, data, NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_exit(1, NULL, ARGV_ERR);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_exit(1, data, ALLOC_ERR);
	parse(data, argv[1]);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!data->mlx_ptr)
		ft_exit(1, data, NULL);

	//mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_key_hook(data->mlx_ptr, (t_mlx_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);

	mlx_terminate(data->mlx_ptr);
	free(data);

	printf("hello world");
	return (0);
}
