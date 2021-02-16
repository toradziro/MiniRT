/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/16 22:36:07 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

void			ray_trace(s_scene *scene)
{
	s_ray		*ray;
	double		coefs[3];
	int			x_pixel;
	int			y_pixel;
	int			res_color;
	s_color		color;

	if (!(ray = (s_ray*)malloc(sizeof(s_ray))))
		killed_by_error(MALLOC_ERROR);
	ray->orig = scene->cams->coordinates;
	x_pixel = 0;
//	printf("fov = %f\n", scene->cams->field_of_v);
//	printf("in rad: %.3f\n", scene->cams->field_of_v * M_PI / 180);
	while (x_pixel < scene->width)
	{
		y_pixel = 0;
		while (y_pixel < scene->height)
		{
			coefs[0] = x_pixel - (scene->width / 2);
			coefs[1] = -y_pixel + (scene->height / 2);
			coefs[2] = scene->width / (2 *tan(scene->cams->field_of_v / 2 * M_PI / 180));
			ray->dir = new_vector(coefs[0], coefs[1], coefs[2]);
			ray->dir = vector_normalise(ray->dir, vector_length(ray->dir));
			color = intersec(scene->figures, ray, scene->lights);
			res_color = color.r << 16 | color.g << 8 | color.b;
			mlx_pixel_put(scene->mlx, scene->window, x_pixel, y_pixel, res_color);
			y_pixel++;
		}
		x_pixel++;
	}
}

s_color			intersec(s_figures *figures, s_ray *ray, s_lights *light)
{
	s_figures	*tmp;
	s_sphere	*sphere_tmp;
	s_color		c_tmp;
	double		min;
	double		intersec;
	//put in another func!
	s_point		*intersec_point;
	s_vector	*normal;
	s_vector	*l_coor = (s_vector*)light->coordinates;
	double		coeff;
	s_color		light_color;
	s_color		res_color;

	tmp = figures;
	min = 1000000;
	c_tmp.r = 0;
	c_tmp.g = 0;
	c_tmp.b = 0;
	light_color = multip_color(light->color, light->intensity);
	while (tmp)
	{
		if (tmp->specif == S_SP)
		{
			//printf("here\n");
			intersec = sphere_intersect(ray, (s_sphere*)tmp->content);
			if (intersec < min && intersec > 0)
			{
				sphere_tmp = (s_sphere*)tmp->content;
				min = intersec;
					//put in another func!
				intersec_point = (s_point*)vector_by_scalar(ray->dir, min);
				normal = subs_vectors((s_vector*)sphere_tmp->coordinates, (s_vector*)intersec_point);
				coeff = vector_scalar_mult(vector_normalise(normal, vector_length(normal)), vector_normalise(l_coor, vector_length(l_coor)));
				coeff *= -1;
				if (coeff < 0)
					coeff = 0;
				light_color = multip_color(light_color, coeff);
				res_color = add_color(sphere_tmp->color, light_color);
			}
		}
		tmp = tmp->next;
	}

	if (min == 1000000)
		return (c_tmp);
	return (res_color);
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
//	double x_two = (-b + sqrt(discr)) / 2;
	// printf("solved with [%.3f %.3f]\n", x_one, x_two);
	if (x_one > 0)
	{
		return (x_one);
	}
	return (0);
}

s_color	multip_color(s_color color, double coeff)
{
	s_color		res;

	res.r = coeff * color.r;
	if (res.r >= 255)
		res.r = 255;
	res.g = coeff * color.g;
	if (res.g >= 255)
		res.g = 255;
	res.b = coeff * color.b;
	if (res.b >= 255)
		res.b = 255;
	return (res);
}

s_color	add_color(s_color color, s_color color_2)
{
	color.r = color.r + color_2.r;
	if (color.r >= 255)
		color.r = 255;
	color.g = color.g + color_2.g;
	if (color.g >= 255)
		color.g = 255;
	color.b = color.b + color_2.b;
	if (color.b >= 255)
		color.b = 255;
	return (color);
}
