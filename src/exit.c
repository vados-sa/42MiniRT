/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:44:52 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/04 14:44:53 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	ft_exit(int exit_code, t_data *data, char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	free_data(data);
	exit(exit_code);
}
