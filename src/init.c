
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

/* //GPT-code in cpp
// Image
auto aspect_ratio = 16.0 / 9.0;
int image_width = 400;
int image_height = static_cast<int>(image_width / aspect_ratio);

// Camera parameters
auto focal_length = 1.0;
auto camera_center = point3(-50.0, 0.0, 20.0);
auto camera_forward = vec3(0.3, 1.0, 0.2).unit_vector(); // Normalize the forward vector

// Choose a world up vector that's not parallel to camera_forward
auto world_up = vec3(0.0, 0.0, 1.0);

// Convert FOV from degrees to radians
t_float FOV_degrees = 70.0;
t_float FOV_radians = FOV_degrees * M_PI / 180.0;

// Calculate viewport width based on FOV and focal length
auto viewport_width = 2.0 * focal_length * tan(FOV_radians / 2.0);

// Calculate viewport height using aspect ratio
auto viewport_height = viewport_width / aspect_ratio;

// Camera basis vectors
auto camera_right = cross(world_up, camera_forward).unit_vector(); // Right direction
auto camera_up = cross(camera_forward, camera_right).unit_vector(); // Up direction

// Position viewport in front of the camera along the forward direction
auto viewport_center = camera_center + focal_length * camera_forward;
auto viewport_upper_left = viewport_center
                         - (viewport_width / 2) * camera_right
                         + (viewport_height / 2) * camera_up;

// Pixel deltas
auto pixel_delta_u = (viewport_width / image_width) * camera_right;
auto pixel_delta_v = -(viewport_height / image_height) * camera_up;

// Upper-left pixel (0,0) location
auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

 */
