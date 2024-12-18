/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:44:52 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/18 12:59:49 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief: frees the general data struct holding all allocated memory
 */
void	free_data(t_data *data)
{
	if (data)
	{
		if (data->image)
			mlx_delete_image(data->mlx_ptr, data->image);
		if (data->mlx_ptr)
			mlx_terminate(data->mlx_ptr);
		if (data->scene)
		{
			if (data->scene->l)
				delete_light_list(&data->scene->l);
			if (data->scene->objects)
				delete_object_list(&data->scene->objects);
			free(data->scene);
		}
		if (data->lines)
			free_arr(data->lines, NULL);
		free(data);
		data = NULL;
	}
}

/**
 * @brief: frees the general struct if necessary,
 * puts an exit message to stdstderr
 * and exits with the provided code
 */
void	ft_exit(int exit_code, t_data *data, char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	free_data(data);
	exit(exit_code);
}
