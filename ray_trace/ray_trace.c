/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/02/27 17:59:31 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

s_color			intersec(s_scene *scene, s_ray *ray)
{
	s_color			c_tmp = {0, 0, 0};
	s_figures		*tmp;
	s_sphere		*sphere_tmp;
	s_plane			*plane_tmp;
	double			min;
	double			intersec;


	tmp = scene->figures;
	min = MAX_INTERSEC;
	while (tmp)
	{
		if (tmp->specif == S_SP)
		{
			intersec = sphere_intersect(ray, (s_sphere*)tmp->content);
			if (intersec < min && intersec > 0)
			{
				sphere_tmp = (s_sphere*)tmp->content;
				min = intersec;
				s_point	*intersec_point = (s_point*)vector_by_scalar(ray->dir, min);
				intersec_point = (s_point*)add_vectors((s_vector*)intersec_point, (s_vector*)scene->cams->coordinates);
				s_vector *normal = subs_vectors((s_vector*)intersec_point, (s_vector*)sphere_tmp->coordinates);
				normal = vector_normalise(normal, vector_length(normal));
				c_tmp = find_color(scene, ray, min, normal, sphere_tmp->color);
			}
		}
		else if (tmp->specif == S_PL)
		{
			intersec = plane_intersect(ray, (s_plane*)tmp->content);
			if (intersec < min && intersec > 0.00001)
			{
				plane_tmp = (s_plane*)tmp->content;
				min = intersec;
				c_tmp = find_color(scene, ray, min, plane_tmp->normal, plane_tmp->color);
			}
		}
		tmp = tmp->next;
	}
	return (c_tmp);
}

s_color			find_color(s_scene *scene, s_ray *ray, double min, s_vector *normal, s_color f_color)
{
	s_point		*intersec_point;
	s_vector	*l_coor;
	double		coeff;
	s_color		res_color;

	intersec_point = (s_point*)vector_by_scalar(ray->dir, min);
	l_coor = subs_vectors((s_vector*)scene->lights->coordinates, (s_vector*)intersec_point);
	if (shadow_intersec(scene->figures, scene->lights, intersec_point, ray) == 1)
			res_color = multip_color(f_color, 0.2);
	else
	{
		coeff = vector_scalar_mult(normal, vector_normalise(l_coor, vector_length(l_coor)));
		coeff = coeff * scene->lights->intensity;
		if (coeff < 0)
			coeff *= -1;
		res_color = final_color(coeff, f_color, scene->ab_light, scene->lights);
	}
	return (res_color);
}

s_color		final_color(double coeff, s_color color, s_ab_light *ab_light, s_lights *light)
{
	s_color	tmp_res = {0, 0, 0};
	s_color	tmp_one;

	while (light)
	{
		tmp_one = multip_color(light->color, light->intensity * coeff);
		tmp_one = normal_color(tmp_one);
		tmp_one = mult_color_by_color(color, tmp_one);
		tmp_res = add_color(tmp_res, tmp_one);
		light = light->next;
	}
	tmp_one = multip_color(ab_light->color, ab_light->intensity);
	tmp_one = normal_color(tmp_one);
	tmp_one = mult_color_by_color(color, tmp_one);
	tmp_res = add_color(tmp_res, tmp_one);
	return (tmp_res);
}

s_color		mult_color_by_color(s_color one, s_color two)
{
	s_color	res;

	res.r = one.r * two.r;
	res.g = one.g * two.g;
	res.b = one.b * two.b;
	return (res);
}

s_color		normal_color(s_color color)
{
	color.r = color.r * COLOR_COEFF;
	color.g = color.g  * COLOR_COEFF;
	color.b = color.b * COLOR_COEFF;
	return (color);
}

s_color		anti_normal_color(s_color color)
{
	color.r = color.r * MAX_COLOR;
	color.g = color.g * MAX_COLOR;
	color.b = color.b * MAX_COLOR;
	if (color.r > MAX_COLOR)
		color.r = MAX_COLOR;
	if (color.g > MAX_COLOR)
		color.g = MAX_COLOR;
	if (color.b > MAX_COLOR)
		color.b = MAX_COLOR;
	return (color);
}

int			shadow_intersec(s_figures *figures, s_lights *lights, s_point *intersec_point, s_ray *orig_ray)
{
	s_figures	*tmp;
	s_figures	*tmp_two;
	s_lights	*light_tmp;
	s_ray		*ray = malloc(sizeof(s_ray));
	double 		res;
	double		x_one;

	light_tmp = lights;
	tmp = figures;
	tmp_two = tmp;
	ray->orig = intersec_point;
	ray->orig = (s_point*)add_vectors((s_vector*)ray->orig, (s_vector*)orig_ray->orig);
	while (light_tmp)
	{
		tmp = tmp_two;
		ray->dir = vector_from_points(intersec_point, light_tmp->coordinates);
		x_one = vector_length(ray->dir);
		ray->dir = vector_normalise(ray->dir, x_one);
		while (tmp->next)
		{
			if (tmp->specif == S_SP)
			{
				res = sphere_intersect(ray, (s_sphere*)tmp->content);
				if (res < x_one && res > 0.0001)
					return (1);
			}
			tmp = tmp->next;
		}
		light_tmp = light_tmp->next;
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
	res = subs_vectors((s_vector*)ray->orig, (s_vector*)sp->coordinates);
	b = 2 * vector_scalar_mult(res, ray->dir);
	c = vector_scalar_mult(res, res) - (sp->radius * sp->radius);
	discr = (b * b) - (4 * c);
	free(res);
	if (discr < 0)
		return (0);
	x_one = (-b - sqrt(discr)) / 2;
//	double x_two = (-b + sqrt(discr)) / 2;
	// printf("solved with [%.3f %.3f]\n", x_one, x_two);
//	printf("%f\n", x_one);
	if (x_one > 0)
		return (x_one);
	return (0);
}

double			plane_intersect(s_ray *ray, s_plane *plane)
{
	double		denom = vector_scalar_mult(plane->normal, ray->dir);
//		printf("%f\n", denom);
	double		t;
	if (denom > 0.000001)
	{
		s_vector *p0l0 = subs_vectors(plane->coordinates, (s_vector*)ray->orig);
		t = vector_scalar_mult(p0l0, plane->normal) / denom;
		if (t >= 0)
			return (t / denom);
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
