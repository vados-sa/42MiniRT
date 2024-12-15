/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:44:46 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/15 14:51:03 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: updates the camera position depending on the key pressed
 */
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

/**
 * @brief: updates the camera position depending on the key pressed
 */
void	zoom(mlx_key_data_t keydata, t_data *data, t_c camera)
{
	if (keydata.key == MLX_KEY_EQUAL || keydata.key == 24 && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_add(camera.center, vec_mult(camera.orientation, 0.1));
	if (keydata.key == MLX_KEY_MINUS || keydata.key == 27 && keydata.action == MLX_PRESS)
		data->scene->c.center = \
		vec_sub(camera.center, vec_mult(camera.orientation, 0.1));
}

/**
 * @brief: updates the camera orientation depending on the key pressed
 */
void	rotate(mlx_key_data_t keydata, t_data *data, t_c camera)
{
	t_matrix3x3	rotation;
	
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		rotation = rotation_matrix(camera.right, 0.1);
		data->scene->c.orientation = vec_unit(apply_rotation(camera.orientation, rotation));
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		rotation = rotation_matrix(camera.right, -0.1);
		data->scene->c.orientation = vec_unit(apply_rotation(camera.orientation, rotation));
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
        rotation = rotation_matrix(camera.up, 0.1);
        data->scene->c.orientation = vec_unit(apply_rotation(camera.orientation, rotation));
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
        rotation = rotation_matrix(camera.up, -0.1);
        data->scene->c.orientation = vec_unit(apply_rotation(camera.orientation, rotation));
	}
	data->scene->c.orientation = vec_unit(data->scene->c.orientation);
}

/**
 * @brief: if ESC is pressed, the window closes and the funtion @returns.
 * otherwise a key press is registered and the viewport is set up
 * according to the updated camera orientation.
 */
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
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A 
		|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_W 
		|| keydata.key == MLX_KEY_MINUS || keydata.key == MLX_KEY_KP_EQUAL 
		|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN 
		|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT )
		setup_viewport(data, data->scene->c);
}

/**
 * @brief: on resizing the window with the mouse, a new image is created
 * and a new viewport is set up according to the new dimensions
 */
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
