/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:44:40 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 15:00:40 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief: main function containing the initialization of the general
 * t_data struct, parsing, viewport initialization, mlx-hooks for rendering,
 * resizing and pressing certain keys, the mlx loop, freeing of data.
 * @return: 0 on success (when closing the mlx window)
 */
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		ft_exit(1, NULL, ARGV_ERR);
	data = init();
	parse(data, argv[1]);
	setup_viewport(data, data->scene->c);
	mlx_loop_hook(data->mlx_ptr, (t_hookfunc)render, data);
	mlx_resize_hook(data->mlx_ptr, (t_resizefunc)resize, data);
	mlx_key_hook(data->mlx_ptr, (t_keyfunc)my_keyhook, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (0);
}
