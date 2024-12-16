/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:36:40 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/16 13:05:47 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define CHECKP 1
# define CHECKS 0
# define SPECULAR 1
# define NUM_THREADS 8

# include "minirt.h"
# include <pthread.h>

typedef struct s_thread_data
{
	t_data		*data;
	uint32_t	start_y;
	uint32_t	end_y;
}	t_thread_data;

t_color		checkerboard(t_intersec *object);
t_color		specular_light(t_l *light, t_intersec *hit_rec, t_data *data);
t_coord		vec_reflect(t_coord incident, t_coord normal);
void		*render_section(void *param);

#endif
