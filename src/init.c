
#include "minirt.h"

void	init(t_data **data)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!*data)
		ft_exit(1, *data, ALLOC_ERR);
	(*data)->scene = ft_calloc(1, sizeof(t_scene));
	if (!(*data)->scene)
		ft_exit(1, *data, ALLOC_ERR);
	(*data)->image_width = IMAGE_WIDTH;
	/* (*data)->scene->l = ft_calloc(1, sizeof(t_L));
	if (!(*data)->scene->l)
		ft_exit(1, *data, ALLOC_ERR);
	(*data)->scene->objects = ft_calloc(1, sizeof(t_object));
	if (!(*data)->scene->objects)
		ft_exit(1, *data, ALLOC_ERR); */
}
/*
void	viewport(t_data *data, t_C camera)
{
	//calculate tetha
	double	radians;
	t_coord	world_up; //should not be parallel to the camera_orientation: either (0.0, 1.0, 0.0) or (0.0, 0.0, 1.0)
	t_coord	camera_right;
	t_coord	camera_up;
	t_coord	vp_center;
	t_coord	vp_upper_left;
	t_coord pixel_delta_u;
	t_coord	pixel_delta_v;

	world_up = coord(0.0, 1.0, 0.0); //add check
	//world_up = coord(0.0, 0.0, 1.0);
	radians = camera.fov * PI / 180.0;
	data->image_height = (int)(IMAGE_WIDTH / ASPECT_RATIO); //check if it rounds correctly
	data->vp_width = 2.0 * FOCAL_LENGTH * tan(radians / 2.0);
	data->vp_height = data->vp_width / ASPECT_RATIO;

	camera_right = vec_unit(vec_cross(world_up, camera.orientation)); //make functions
	camera_up = vec_unit(vec_cross(camera.orientation, camera_right));

	vp_center = vec_add(camera.center, vec_mult(FOCAL_LENGTH, camera.orientation)); //make functions
	vp_upper_left = vp_center - vec_mult((data->vp_width / 2), camera_right) + vec_mult((data->vp_height / 2), camera_up)



}

//GPT-code in cpp
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
double FOV_degrees = 70.0;
double FOV_radians = FOV_degrees * M_PI / 180.0;

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
