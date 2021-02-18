/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/18 22:11:28 by ehillman         ###   ########.fr       */
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
			color = intersec(scene->figures, ray, scene->lights, scene->ab_light);
			res_color = color.r << 16 | color.g << 8 | color.b;
			mlx_pixel_put(scene->mlx, scene->window, x_pixel, y_pixel, res_color);
			y_pixel++;
		}
		x_pixel++;
	}
}

s_color			intersec(s_figures *figures, s_ray *ray, s_lights *light, s_ab_light *ab_light)
{
	s_figures	*tmp;
	s_sphere	*sphere_tmp;
//	s_vector	*normal;
	s_color		c_tmp;
	double		min;
	double		intersec;


	tmp = figures;
	min = 1000000;
	c_tmp.r = 0;
	c_tmp.g = 0;
	c_tmp.b = 0;
	while (tmp)
	{
		if (tmp->specif == S_SP)
		{
			intersec = sphere_intersect(ray, (s_sphere*)tmp->content);
			if (intersec < min && intersec > 0)
			{
				sphere_tmp = (s_sphere*)tmp->content;
				min = intersec;
				c_tmp = find_color(ab_light, light, ray, min, sphere_tmp, figures);
			}
		}
		tmp = tmp->next;
	}
	return (c_tmp);
}

s_color			find_color(s_ab_light *ab_light, s_lights *light, s_ray *ray, double min, s_sphere *sphere, s_figures *figures)
{
	s_point		*intersec_point;
	s_vector	*normal;
	s_vector	*l_coor = (s_vector*)light->coordinates;
	double		coeff;
	s_color		light_color;
	s_color		res_color;

	s_ray		*shadow_ray = malloc(sizeof(s_ray));

	light_color = multip_color(light->color, light->intensity);
	intersec_point = (s_point*)vector_by_scalar(ray->dir, min);
	normal = subs_vectors((s_vector*)sphere->coordinates, (s_vector*)intersec_point);
	shadow_ray->orig = intersec_point;

	l_coor = (s_vector*)subs_vectors(l_coor, (s_vector*)intersec_point);
	shadow_ray->dir = subs_vectors((s_vector*)light->coordinates, (s_vector*)intersec_point);
	shadow_ray->dir = vector_normalise(shadow_ray->dir, vector_length(shadow_ray->dir));
	printf("%f, %f, %f\n", shadow_ray->dir->v_x, shadow_ray->dir->v_y, shadow_ray->dir->v_z);

	if (shadow_intersec(figures, shadow_ray))
	//	res_color = multip_color(sphere->color, ab_light->intensity);
	{
		printf("HERE!!!");
		res_color.r = 24;
		res_color.g = 31;
		res_color.b = 82;
	}
	else
	{
		coeff = vector_scalar_mult(vector_normalise(normal, vector_length(normal)), vector_normalise(l_coor, vector_length(l_coor)));
		coeff *= -1;
		if (coeff < 0)
			coeff = 0;
		res_color = multip_color(sphere->color, (coeff * light->intensity + ab_light->intensity));
	}
	return (res_color);
}

int			shadow_intersec(s_figures *figures, s_ray *ray)
{
	s_figures	*tmp;
//	s_vector	*normal;

	double res;
	tmp = figures;
	while (tmp->next)
	{
		if (tmp->specif == S_SP)
		{
			res = sphere_intersect(ray, (s_sphere*)tmp->content);
			if (res < 1000000 && res > 0.001)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

double			sphere_intersect(s_ray *ray, s_sphere *sp)
{
	double		b;
	double		c;
	double		discr;
	double		x_one;
	s_vector	*res;

	x_one = 0;
	//static int i;
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
