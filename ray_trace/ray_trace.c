/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/11 22:43:47 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

void			ray_trace(void *mlx, void *window, s_scene *scene)
{
	s_ray		*ray;
	double		coefs[3];
	int			x_pixel;
	int			y_pixel;
	int			res_color;
	s_color		*color;

	if (!(ray = (s_ray*)malloc(sizeof(s_ray))))
		killed_by_error(MALLOC_ERROR);
	ray->orig = scene->cams->coordinates;
	x_pixel = 0;
	printf("fov = %f\n", scene->cams->field_of_v);
//	printf("in rad: %.3f\n", scene->cams->field_of_v * M_PI / 180);
	return ;
	while (x_pixel < scene->width)
	{
		y_pixel = 0;
		while (y_pixel < scene->height)
		{
			coefs[0] = x_pixel - (scene->width / 2);
			coefs[1] = -y_pixel + (scene->height / 2);
			coefs[2] = scene->width / (2 *tan(scene->cams->field_of_v / 2 * M_PI / 180));
			ray->dir = new_vector(coefs[0], coefs[1], coefs[2]);
			// if (x_pixel % 10 == 0 && y_pixel % 10 == 0)
			// {
			// 	printf("[%d %d]\t", x_pixel, y_pixel);
			// 	printf("[%.1f %.1f %.1f]\n", coefs[0], coefs[1], coefs[2]);
			// }
			ray->dir = vector_normalise(ray->dir, vector_length(ray->dir));
			color = intersec(scene->figures, ray);
			//free (ray);
			if (color)
				res_color = color->r << 16 | color->g << 8 | color->b;
			else
				res_color = 0;
			mlx_pixel_put(mlx, window, x_pixel, y_pixel, res_color);
			y_pixel++;
		}
		x_pixel++;
	}
}

s_color			*intersec(s_figures *figures, s_ray *ray)
{
	s_figures	*tmp;
	s_sphere	*sphere_tmp;
	double		min;
	double		intersec;

	tmp = figures;
	min = 100000;
	while (tmp)
	{
		if (tmp->specif == S_SP)
		{
			//printf("here\n");
			intersec = sphere_intersect(ray, (s_sphere*)tmp->content);
			if (intersec > 0)
				printf("inter = %f\n", intersec);
			if (intersec < min && intersec > 0)
			{
				printf("min = %.3f\n", min);
				printf("intersec = %.3f\n", min);
				sphere_tmp = (s_sphere*)tmp->content;
				min = intersec;
				printf("min after= %.3f\n", min);
				printf("intersec after = %.3f\n", min);
			}
		}
		tmp = tmp->next;
	}
	if (min == 100000)
		return (NULL);
	return (&(sphere_tmp->color));
}

double			sphere_intersect(s_ray *ray, s_sphere *sp)
{
	double		b;
	double		c;
	double		discr;
	double		x_one;
	s_vector	*res;

	x_one = 0;
	res = subs_vectors(ray->dir, (s_vector*)sp->coordinates);
	b = 2 * vector_scalar_mult(res, ray->dir);
	c = vector_scalar_mult(res, res) - (sp->radius * sp->radius);
	discr = (b * b) - (4 * c);
	free(res);
	if (discr < 0)
		return (0);
	x_one = (-b - sqrt(discr)) / 2;
	double x_two = (-b + sqrt(discr)) / 2;
	// printf("solved with [%.3f %.3f]\n", x_one, x_two);
	if (x_one > 0)
	{
		printf("here\n");
		return (x_one);
	}
	return (0);
}
