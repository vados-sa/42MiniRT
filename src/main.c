
#include "minirt.h"

void	my_keyhook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx_ptr);
		//ft_exit(0, data, NULL);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		data->scene->c.center.y -= 0.01;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		data->scene->c.center.y += 0.01;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->scene->c.center.x -= 0.01;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->scene->c.center.x += 0.01;
}

void	resize(int32_t width, int32_t height, t_data *data)
{
	mlx_delete_image(data->mlx_ptr, data->image);
	data->image = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->image
		|| mlx_image_to_window(data->mlx_ptr, data->image, 0, 0))
		ft_exit(1, data, NULL);
	data->image_width = width;
	data->image_height = height;
	setup_viewport(data, data->scene->c);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_exit(1, NULL, ARGV_ERR);
	init(&data);
	parse(data, argv[1]);
	setup_viewport(data, data->scene->c);
	//render(data);
	mlx_loop_hook(data->mlx_ptr, (t_hookfunc)render, data);
	mlx_resize_hook(data->mlx_ptr, (t_resizefunc)resize, data);
	mlx_key_hook(data->mlx_ptr, (t_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (0);
}
