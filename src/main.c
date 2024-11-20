
#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_exit(1, NULL, ARGV_ERR);
	init(&data);
	parse(data, argv[1]);
	setup_viewport(data, data->scene->c);
	mlx_loop_hook(data->mlx_ptr, (t_hookfunc)render, data);
	mlx_resize_hook(data->mlx_ptr, (t_resizefunc)resize, data);
	mlx_key_hook(data->mlx_ptr, (t_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (0);
}
