void print_vp(t_vp vp) {
    printf("\nViewport Width: %.15lf\n", vp.width);
    printf("Viewport Height: %.15lf\n", vp.height);
    printf("Viewport Center: (%.15lf, %.15lf, %.15lf)\n", vp.center.x, vp.center.y, vp.center.z);
    printf("Viewport Up Left: (%.15lf, %.15lf, %.15lf)\n", vp.up_left.x, vp.up_left.y, vp.up_left.z);
    printf("Pixel X: (%.15lf, %.15lf, %.15lf)\n", vp.pixel_x.x, vp.pixel_x.y, vp.pixel_x.z);
    printf("Pixel Y: (%.15lf, %.15lf, %.15lf)\n", vp.pixel_y.x, vp.pixel_y.y, vp.pixel_y.z);
    printf("Pixel 00: (%.15lf, %.15lf, %.15lf)\n", vp.pixel00.x, vp.pixel00.y, vp.pixel00.z);
}

void setup_viewport(t_data *data, t_C camera)
{
    t_coord world_up;
    t_coord camera_right;
    t_coord camera_up;

    world_up = coord(0.0, 1.0, 0.0);
    if (camera.orientation.y == 1.0 || camera.orientation.y == -1.0) // check if world_up is not parallel to camera_orientation
        world_up = coord(0.0, 0.0, 1.0);

    printf("Camera FOV: %.15lf\n", camera.fov);
    data->vp.width = 2.0 * tan((camera.fov * PI / 180.0) / 2.0);
    printf("Viewport Width after tan: %.15lf\n", data->vp.width);

    data->vp.height = data->vp.width / ((t_float)IMAGE_WIDTH / (t_float)IMAGE_HEIGHT);
    printf("Viewport Height: %.15lf\n", data->vp.height);

    camera_right = vec_unit(vec_cross(world_up, camera.orientation));
    printf("Camera Right: (%.15lf, %.15lf, %.15lf)\n", camera_right.x, camera_right.y, camera_right.z);

    camera_up = vec_unit(vec_cross(camera.orientation, camera_right));
    printf("Camera Up: (%.15lf, %.15lf, %.15lf)\n", camera_up.x, camera_up.y, camera_up.z);

    data->vp.center = vec_add(camera.center, vec_mult(camera.orientation, FOCAL_LENGTH));
    printf("Viewport Center: (%.15lf, %.15lf, %.15lf)\n", data->vp.center.x, data->vp.center.y, data->vp.center.z);

    data->vp.up_left = vec_add(vec_sub(data->vp.center, vec_mult(camera_right, (data->vp.width / 2))), vec_mult(camera_up, (data->vp.height / 2)));
    printf("Viewport Up Left: (%.15lf, %.15lf, %.15lf)\n", data->vp.up_left.x, data->vp.up_left.y, data->vp.up_left.z);

	printf("Camera Right: (%.15lf, %.15lf, %.15lf)\n", camera_right.x, camera_right.y, camera_right.z);
	printf("Viewport Width: %.15lf\n", data->vp.width);
	printf("Image Width: %f\n", data->image_width);
	printf("Image Height: %f\n", data->image_height);

    data->vp.pixel_x = vec_mult(camera_right, (data->vp.width / data->image_width));
    printf("Pixel X: (%.15lf, %.15lf, %.15lf)\n", data->vp.pixel_x.x, data->vp.pixel_x.y, data->vp.pixel_x.z);

    data->vp.pixel_y = vec_mult(camera_up, -(data->vp.height / data->image_height));
    printf("Pixel Y: (%.15lf, %.15lf, %.15lf)\n", data->vp.pixel_y.x, data->vp.pixel_y.y, data->vp.pixel_y.z);

    data->vp.pixel00 = vec_add(data->vp.up_left, vec_mult(vec_add(data->vp.pixel_x, data->vp.pixel_y), 0.5));
    printf("Pixel 00: (%.15lf, %.15lf, %.15lf)\n", data->vp.pixel00.x, data->vp.pixel00.y, data->vp.pixel00.z);

    //print_vp(data->vp);
}
