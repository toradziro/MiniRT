#include "includes/MiniRT.h"

void	threads(s_scene *scene)
{
	int				i;
	s_thread		thread_id[THREADS_MAX];
	pthread_t		thread[THREADS_MAX];

	i = 0;
	scene->img.img = mlx_new_image(scene->mlx, scene->width, scene->height);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bits_per_pixel, &scene->img.line_length, &scene->img.endian);
	scene->mtrx = matrix_place(scene->cams->coordinates, scene->cams->direction);
	while (i < THREADS_MAX)
	{
		thread_id[i].id = i;
		thread_id[i].scene = (s_scene*)malloc(sizeof(s_scene));
		memcpy(thread_id[i].scene, scene, sizeof(s_scene));
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
	if (scene->is_save)
	{
		save_to_bmp(scene);
		exit_rt(scene);
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->img.img, 0, 0);
}

void			*ray_trace_thread(void* thread)
{
	s_thread 	*curr_thr = (s_thread*)thread;
	s_scene		*scene = curr_thr->scene;
	int max_pixel_x = scene->width / THREADS_MAX;
	s_ray		ray;
	s_color		color;
	float		coefs[3];
	int			x_pixel;
	int			y_pixel;
	int			y_end;
	int			res_color;

	y_pixel = curr_thr->id * (scene->height / THREADS_MAX);
	y_end = y_pixel + (scene->height / THREADS_MAX);
	ray.orig = scene->cams->coordinates;

	while (y_pixel < y_end)
	{
		x_pixel = 0;
		while (x_pixel < scene->width)
		{
			coefs[1] = -y_pixel + (scene->height * 0.5);
			coefs[0] = x_pixel - (scene->width * 0.5);
			coefs[2] = scene->width / (2 * tan(scene->cams->field_of_v * 0.5 * M_PI * 0.00555555555));
			ray.dir = new_vector(coefs[0], coefs[1], coefs[2]);
			ray.dir = matrix_mult(ray.dir, scene->mtrx);
			ray.dir = vector_normalise(&ray.dir);
			color = intersec(scene, &ray);
			res_color = (int)color.r << 16 | (int)color.g << 8 | (int)color.b;
			my_mlx_pixel_put(&scene->img, x_pixel, y_pixel, res_color);
			x_pixel++;
		}
		y_pixel++;
	}
	pthread_exit(NULL);
}
