
#include "minirt.h"

void	my_keyhook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx_ptr);
		//ft_exit(0, data, NULL);
}

void	setup_viewport(t_data *data, t_C camera)
{
	t_coord	world_up;
	t_coord	camera_right;
	t_coord	camera_up;

	world_up = coord(0.0, 1.0, 0.0);
	if (camera.orientation.y == 1.0 || camera.orientation.y == -1) //check if world_up is not parallel to camera_orientation
		world_up = coord(0.0, 0.0, 1.0);
	data->vp.width = 2.0 * tan((camera.fov * PI / 180.0) / 2.0);
	data->vp.height = data->vp.width / ((double)IMAGE_WIDTH / (double)IMAGE_HEIGHT);
	camera_right = vec_unit(vec_cross(camera.orientation, world_up));
	camera_up = vec_unit(vec_cross(camera_right, camera.orientation));
	data->vp.center = vec_add(camera.center, vec_mult(camera.orientation, \
						FOCAL_LENGTH));
	data->vp.up_left = vec_add(vec_sub(data->vp.center, \
	vec_mult(camera_right, (data->vp.width / 2))), \
	vec_mult(camera_up, (data->vp.height / 2)));
	data->vp.pixel_x = vec_mult(camera_right, (data->vp.width / \
					data->image_width));
	data->vp.pixel_y = vec_mult(camera_up, -(data->vp.height / \
					data->image_height));
	data->vp.pixel00 = vec_add(data->vp.up_left, \
	vec_mult((vec_add(data->vp.pixel_x, data->vp.pixel_y)), 0.5));
}

void print_vp(t_vp vp) {
    printf("\nViewport Width: %.15lf\n", vp.width);
    printf("Viewport Height: %.15lf\n", vp.height);
    printf("Viewport Center: (%.15lf, %.15lf, %.15lf)\n", vp.center.x, vp.center.y, vp.center.z);
    printf("Viewport Up Left: (%.15lf, %.15lf, %.15lf)\n", vp.up_left.x, vp.up_left.y, vp.up_left.z);
    printf("Pixel X: (%.15lf, %.15lf, %.15lf)\n", vp.pixel_x.x, vp.pixel_x.y, vp.pixel_x.z);
    printf("Pixel Y: (%.15lf, %.15lf, %.15lf)\n", vp.pixel_y.x, vp.pixel_y.y, vp.pixel_y.z);
    printf("Pixel 00: (%.15lf, %.15lf, %.15lf)\n", vp.pixel00.x, vp.pixel00.y, vp.pixel00.z);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_exit(1, NULL, ARGV_ERR);
	init(&data);
	parse(data, argv[1]);
	draw_background(data);
	setup_viewport(data, data->scene->c);
	print_vp(data->vp);
	//mlx_loop_hook(data->mlx_ptr, &draw_background, data);
	//mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_key_hook(data->mlx_ptr, (t_mlx_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);
	//print_data(data);
	free_data(data);
	return (0);
}
