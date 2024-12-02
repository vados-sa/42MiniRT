
#include "minirt.h"

t_data	*init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_exit(1, data, ALLOC_ERR);
	(data)->scene = ft_calloc(1, sizeof(t_scene));
	if (!(data)->scene)
		ft_exit(1, data, ALLOC_ERR);
	(data)->image_width = (t_float)IMAGE_WIDTH;
	(data)->image_height = (t_float)IMAGE_HEIGHT;
	(data)->mlx_ptr = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "miniRT", true);
	if (!(data)->mlx_ptr)
	{
		mlx_close_window((data)->mlx_ptr);
		ft_exit(1, data, NULL);
	}
	(data)->image = mlx_new_image((data)->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!(data)->image
		|| mlx_image_to_window((data)->mlx_ptr, (data)->image, 0, 0))
	{
		mlx_close_window((data)->mlx_ptr);
		ft_exit(1, data, NULL);
	}
	return (data);
}

void	setup_viewport(t_data *data, t_c camera)
{
	t_coord	world_up;

	world_up = coord(0.0, 1.0, 0.0);
	if (fabs(camera.orientation.y - 1) < EPSILON || \
	fabs(camera.orientation.y + 1) < EPSILON)
		world_up = coord(0.0, 0.0, 1.0);
	data->vp.width = 2.0 * FOCAL_LENGTH * tan((camera.fov * PI / 180.0) / 2.0);
	data->vp.height = data->vp.width / (data->image_width / data->image_height);
	camera.right = vec_unit(vec_cross(camera.orientation, world_up));
	camera.up = vec_unit(vec_cross(camera.right, camera.orientation));
	data->vp.center = vec_add(camera.center, vec_mult(camera.orientation, \
						FOCAL_LENGTH));
	data->vp.up_left = vec_add(vec_sub(data->vp.center, \
	vec_mult(camera.right, (data->vp.width / 2))), \
	vec_mult(camera.up, (data->vp.height / 2)));
	data->vp.pixel_x = vec_mult(camera.right, (data->vp.width / \
					data->image_width));
	data->vp.pixel_y = vec_mult(camera.up, -(data->vp.height / \
					data->image_height));
	data->vp.pixel00 = vec_add(data->vp.up_left, \
	vec_mult((vec_add(data->vp.pixel_x, data->vp.pixel_y)), 0.5));
	data->scene->c.up = camera.up;
	data->scene->c.right = camera.right;
}
