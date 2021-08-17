/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:46:41 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:32:06 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/MiniRT.h"

void			threads(t_scene *scene)
{
	int			i;
	t_thread	thread_id[THREADS_MAX];
	pthread_t	thread[THREADS_MAX];

	i = 0;
	scene->img.img = mlx_new_image(scene->mlx, scene->width, scene->height);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
					&scene->img.bits_per_pixel, &scene->img.line_length,
					&scene->img.endian);
	scene->mtrx = matrix_place(scene->cams->coordinates,
					scene->cams->direction);
	threads_start(thread_id, thread, scene);
	if (scene->is_save)
	{
		save_to_bmp(scene);
		mlx_destroy_image(scene->mlx, scene->img.img);
		exit_rt(scene);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->img.img, 0, 0);
}

void			threads_start(t_thread *thread_id,
				pthread_t *thread, t_scene *scene)
{
	int			i;

	i = 0;
	while (i < THREADS_MAX)
	{
		thread_id[i].id = i;
		thread_id[i].scene = *scene;
		if (pthread_create(&thread[i], NULL, ray_trace_thread, &thread_id[i]))
			killed_by_error(MALLOC_ERROR);
		++i;
	}
	i = 0;
	while (i < THREADS_MAX)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
}

void			*ray_trace_thread(void *thread)
{
	t_ray_trace	trace;

	trace.curr_thr = (t_thread*)thread;
	trace.scene = &(trace.curr_thr->scene);
	trace.y_pixel = trace.curr_thr->id * (trace.scene->height / THREADS_MAX);
	trace.y_end = trace.y_pixel + (trace.scene->height / THREADS_MAX);
	trace.ray.orig = trace.scene->cams->coordinates;
	main_rt_loop(trace);
	pthread_exit(NULL);
}

void			main_rt_loop(t_ray_trace trace)
{
	while (trace.y_pixel < trace.y_end)
	{
		trace.x_pixel = 0;
		while (trace.x_pixel < trace.scene->width)
		{
			trace.coefs[1] = -trace.y_pixel + (trace.scene->height * 0.5);
			trace.coefs[0] = trace.x_pixel - (trace.scene->width * 0.5);
			trace.coefs[2] = trace.scene->width / (2 *
			tan(trace.scene->cams->field_of_v * 0.5 * M_PI * 0.00555555555));
			trace.ray.dir = new_vector(trace.coefs[0],
							trace.coefs[1], trace.coefs[2]);
			trace.ray.dir = matrix_mult(trace.ray.dir, trace.scene->mtrx);
			trace.ray.dir = vector_normalise(trace.ray.dir);
			trace.color = intersec(trace.scene, trace.ray);
			trace.ret_color = (int)trace.color.r << 16 |
							(int)trace.color.g << 8 | (int)trace.color.b;
			my_mlx_pixel_put(&trace.scene->img,
							trace.x_pixel, trace.y_pixel, trace.ret_color);
			trace.x_pixel++;
		}
		trace.y_pixel++;
	}
}
