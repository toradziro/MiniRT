/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:45 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:34:54 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H
# include "minirt.h"
# include "pthread.h"
# include "intersect.h"

typedef struct		s_thread{
	int				id;
	t_scene			scene;
}					t_thread;

typedef struct		s_ray_trace{
	t_thread		*curr_thr;
	t_scene			*scene;
	t_ray			ray;
	t_color			color;
	float			coefs[3];
	int				x_pixel;
	int				y_pixel;
	int				y_end;
	int				ret_color;
}					t_ray_trace;

void				*ray_trace_thread(void *thread);
void				threads_start(t_thread *thread_id,
					pthread_t *thread, t_scene *scene);
void				threads(t_scene *scene);
void				main_rt_loop(t_ray_trace trace);

#endif
