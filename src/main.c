
#include "minirt.h"

void	my_keyhook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx_ptr);
		//ft_exit(0, data, NULL);
}

void print_vp(t_vp vp) {
    printf("Viewport Width: %lf\n", vp.width);
    printf("Viewport Height: %lf\n", vp.height);
    printf("Viewport Center: (%lf, %lf, %lf)\n", vp.center.x, vp.center.y, vp.center.z);
    printf("Viewport Up Left: (%lf, %lf, %lf)\n", vp.up_left.x, vp.up_left.y, vp.up_left.z);
    printf("Pixel X: (%lf, %lf, %lf)\n", vp.pixel_x.x, vp.pixel_x.y, vp.pixel_x.z);
    printf("Pixel Y: (%lf, %lf, %lf)\n", vp.pixel_y.x, vp.pixel_y.y, vp.pixel_y.z);
    printf("Pixel 00: (%lf, %lf, %lf)\n", vp.pixel00.x, vp.pixel00.y, vp.pixel00.z);
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
	data->vp.height = data->vp.width / (IMAGE_WIDTH / IMAGE_HEIGHT);
	camera_right = vec_unit(vec_cross(world_up, camera.orientation));
	camera_up = vec_unit(vec_cross(camera.orientation, camera_right));
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
	print_vp(data->vp);
}

// Helper function to print t_coord
void print_coordinate(t_coord coord) {
    printf("Coordinate (x, y, z): (%lf, %lf, %lf)\n", coord.x, coord.y, coord.z);
}

// Helper function to print t_color
void print_color(t_color color) {
    printf("Color (r, g, b): (%d, %d, %d)\n", color.r, color.g, color.b);
}

// Print function for t_A
void print_A(t_A a) {
    printf("Ambient Light Ratio: %lf\n", a.ratio);
    print_color(a.color);
}

// Print function for t_C
void print_C(t_C c) {
    printf("Camera View Point:\n");
    print_coordinate(c.center);
    printf("Camera Normal:\n");
    print_coordinate(c.orientation);
    printf("Camera Field of View: %lf\n", c.fov);
}

// Print function for t_L linked list
void print_L(t_L *l) {
    while (l) {
        printf("Light Point:\n");
        print_coordinate(l->point);
        printf("Light Brightness: %lf\n", l->brightness);
        print_color(l->color);
        l = l->next;
    }
}

// Print function for t_plane
void print_plane(t_plane pl) {
    printf("Plane Point:\n");
    print_coordinate(pl.point);
    printf("Plane Normal:\n");
    print_coordinate(pl.normal);
    print_color(pl.color);
}

// Print function for t_sphere
void print_sphere(t_sphere sp) {
    printf("Sphere Center:\n");
    print_coordinate(sp.center);
    printf("Sphere Diameter: %lf\n", sp.diameter);
    print_color(sp.color);
}

// Print function for t_cylinder
void print_cylinder(t_cylinder cy) {
    printf("Cylinder Center:\n");
    print_coordinate(cy.center);
    printf("Cylinder Normal:\n");
    print_coordinate(cy.normal);
    printf("Cylinder Diameter: %lf\n", cy.diameter);
    printf("Cylinder Height: %lf\n", cy.height);
    print_color(cy.color);
}

// Print function for t_object linked list
void print_object(t_object *obj) {
    while (obj) {
        printf("Object Type: %c\n", obj->type);
        if (obj->type == 'p') {
            print_plane(obj->pl);
        } else if (obj->type == 's') {
            print_sphere(obj->sp);
        } else if (obj->type == 'c') {
            print_cylinder(obj->cy);
        }
        printf("Object Flag: %d\n", obj->flag);
        obj = obj->next;
    }
}

// Print function for t_scene
void print_scene(t_scene *scene) {
    printf("Scene Ambient Light:\n\n");
    print_A(scene->a);
    printf("Scene Camera:\n\n");
    print_C(scene->c);
    printf("Scene Lights:\n\n");
    print_L(scene->l);
    printf("Scene Objects:\n\n");
    print_object(scene->objects);
}

// Print function for t_data
void print_data(t_data *data) {
    //printf("Window Width: %d, Height: %d\n", data->width, data->height);
    printf("Scene:\n");
    print_scene(data->scene);
    if (data->lines) {
        printf("Lines:\n");
        for (int i = 0; data->lines[i] != NULL; i++) {
            printf("%s\n", data->lines[i]);
        }
    }
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_exit(1, NULL, ARGV_ERR);
	init(&data);
	parse(data, argv[1]);
	draw_background(data);
	print_data(data);
	setup_viewport(data, data->scene->c);
	//mlx_loop_hook(data->mlx_ptr, &draw_background, data);
	//mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_key_hook(data->mlx_ptr, (t_mlx_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);

	//print_data(data);

	free_data(data);
	return (0);
}
