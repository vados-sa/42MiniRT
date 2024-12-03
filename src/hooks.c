
#include "minirt.h"

void	move(mlx_key_data_t keydata, t_data *data, t_c camera)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_add(camera.center, vec_mult(camera.up, 0.1));
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_sub(camera.center, vec_mult(camera.up, 0.1));
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_add(camera.center, vec_mult(camera.right, 0.1));
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_sub(camera.center, vec_mult(camera.right, 0.1));
}

void	zoom(mlx_key_data_t keydata, t_data *data, t_c camera)
{
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_add(camera.center, vec_mult(camera.orientation, 0.1));
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_sub(camera.center, vec_mult(camera.orientation, 0.1));
}

void	rotate(mlx_key_data_t keydata, t_data *data, t_c camera)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		data->scene->c.orientation = \
		vec_unit(vec_add(camera.orientation, vec_mult(camera.up, 0.1)));
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		data->scene->c.orientation = \
		vec_unit(vec_sub(camera.orientation, vec_mult(camera.up, 0.1)));
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		data->scene->c.orientation = \
		vec_unit(vec_sub(camera.orientation, vec_mult(camera.right, 0.1)));
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		data->scene->c.orientation = \
		vec_unit(vec_add(camera.orientation, vec_mult(camera.right, 0.1)));
}

void	my_keyhook(mlx_key_data_t keydata, t_data *data)
{
	t_c	camera;

	camera = data->scene->c;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx_ptr);
		return ;
	}
	move(keydata, data, camera);
	zoom(keydata, data, camera);
	rotate(keydata, data, camera);
	setup_viewport(data, data->scene->c);
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
