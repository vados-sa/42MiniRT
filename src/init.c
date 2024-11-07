
#include "minirt.h"

void	init(t_data **data)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!*data)
		ft_exit(1, *data, ALLOC_ERR);
	(*data)->scene = ft_calloc(1, sizeof(t_scene));
	if (!(*data)->scene)
		ft_exit(1, *data, ALLOC_ERR);
	(*data)->image_width = (t_float)IMAGE_WIDTH;
	(*data)->image_height = (t_float)IMAGE_HEIGHT;
	(*data)->mlx_ptr = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "miniRT", true);
	if (!(*data)->mlx_ptr)
		ft_exit(1, *data, NULL);
	(*data)->image = mlx_new_image((*data)->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!(*data)->image || mlx_image_to_window((*data)->mlx_ptr, (*data)->image, 0, 0))
		ft_exit(1, *data, NULL);
	/* (*data)->scene->l = ft_calloc(1, sizeof(t_L));
	if (!(*data)->scene->l)
		ft_exit(1, *data, ALLOC_ERR);
	(*data)->scene->objects = ft_calloc(1, sizeof(t_object));
	if (!(*data)->scene->objects)
		ft_exit(1, *data, ALLOC_ERR); */
}

void	setup_viewport(t_data *data, t_C camera)
{
	t_coord	world_up;
	t_coord	camera_right;
	t_coord	camera_up;

	world_up = coord(0.0, 1.0, 0.0);
	if (fabs(camera.orientation.y) == 1.0) //check if world_up is not parallel to camera_orientation
		world_up = coord(0.0, 0.0, 1.0);
	data->vp.width = 2.0 * FOCAL_LENGTH * tan((camera.fov * PI / 180.0) / 2.0);
	data->vp.height = data->vp.width / ((t_float)data->image_width / (t_float)data->image_height);
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
	data->scene->c.up = camera_up;
	data->scene->c.right = camera_right;

	printf("world_up: (%f, %f, %f)\n", world_up.x, world_up.y, world_up.z);
	printf("camera_right: (%f, %f, %f)\n", camera_right.x, camera_right.y, camera_right.z);
	printf("camera_up: (%f, %f, %f)\n", camera_up.x, camera_up.y, camera_up.z);
	printf("vp.width: %f\n", data->vp.width);
	printf("vp.height: %f\n", data->vp.height);
	printf("vp.center: (%f, %f, %f)\n", data->vp.center.x, data->vp.center.y, data->vp.center.z);
	printf("vp.up_left: (%f, %f, %f)\n", data->vp.up_left.x, data->vp.up_left.y, data->vp.up_left.z);
	printf("vp.pixel_x: (%f, %f, %f)\n", data->vp.pixel_x.x, data->vp.pixel_x.y, data->vp.pixel_x.z);
	printf("vp.pixel_y: (%f, %f, %f)\n", data->vp.pixel_y.x, data->vp.pixel_y.y, data->vp.pixel_y.z);
	printf("vp.pixel00: (%f, %f, %f)\n", data->vp.pixel00.x, data->vp.pixel00.y, data->vp.pixel00.z);

}
