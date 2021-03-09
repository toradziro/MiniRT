/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/10 00:00:04 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"



s_color			intersec(s_scene *scene, s_ray ray)
{
	s_color			c_tmp = {0, 0, 0};
	s_figures		*tmp;
	s_sphere		*sphere_tmp;
	s_plane			*plane_tmp;
	float			min;
	float			intersec;
	int				i;
	int				finish;

	i = 0;
	tmp = scene->figures->node;
	finish = scene->figures->length;
	min = MAX_INTERSEC;
	while (i < finish)
	{
		if (tmp[i].specif == S_SP)
		{
			intersec = sphere_intersect(ray, (s_sphere*)tmp[i].content);
			if (intersec < min && intersec > MIN_I)
			{
				sphere_tmp = (s_sphere*)tmp[i].content;
				min = intersec;
				s_vector	intersec_point = vector_by_scalar(ray.dir, min);
				intersec_point = add_vectors(intersec_point, scene->cams->coordinates);
				s_vector normal = subs_vectors(intersec_point, sphere_tmp->coordinates);
				normal = vector_normalise(normal);
				c_tmp = find_color(scene, &ray, min, normal, &sphere_tmp->color);
			}
		}
		else if (tmp[i].specif == S_PL)
		{
			plane_tmp = (s_plane*)tmp[i].content;
			intersec = plane_intersect(ray, plane_tmp);
			if (intersec < min && intersec > MIN_I)
			{
				min = intersec;
				c_tmp = find_color(scene, &ray, min, plane_tmp->normal, &plane_tmp->color);
			}
		}
		else if (tmp[i].specif == S_TR)
		{
			intersec = triangle_intersec(&ray, (s_triangle*)tmp[i].content);
			if (intersec < min && intersec > MIN_I)
			{
				s_triangle *triangle_tmp = (s_triangle*)tmp[i].content;
				min = intersec;
				c_tmp = find_color(scene, &ray, min, triangle_tmp->normal, &triangle_tmp->color);
			}
		}
		else if (tmp[i].specif == S_SQ)
		{
			intersec = square_intersec(ray, (s_square*)tmp[i].content, min);
			if (intersec < min && intersec > MIN_I)
			{
				s_square *square_tmp = (s_square*)tmp[i].content;
				min = intersec;
				c_tmp = find_color(scene, &ray, min, square_tmp->normal, &square_tmp->color);
			}
		}
		// else if (tmp[i].specif == S_CL)
		// {
		// 	//?????
		// }
		++i;
	}
	return (c_tmp);
}

s_color			find_color(s_scene *scene, s_ray *ray, float min, s_vector normal, s_color *f_color)
{
	s_vector	intersec_point;
	float		coeff;
	s_color		res_color;
	s_phong		phong;
	s_vector	dir_to_light;
	s_lights	*tmp_light;

	if (vector_scalar_mult(ray->dir, normal) > 0)
		normal = vector_by_scalar(normal, -1);

	tmp_light = scene->lights;
	intersec_point = vector_by_scalar(ray->dir, min);
	intersec_point = add_vectors(intersec_point, ray->orig);
	res_color = shad_color(*f_color, scene->ab_light->color);
	while (tmp_light)
	{
		dir_to_light = subs_vectors(tmp_light->coordinates, intersec_point);

		if (!(shadow_intersec(scene->figures, tmp_light, &intersec_point, &dir_to_light)))
		{
			dir_to_light = vector_normalise(dir_to_light);
			phong = calc_phong(intersec_point, scene, normal);
			coeff = vector_scalar_mult(normal, dir_to_light);
			if (coeff < 0)
				coeff = 0;
			coeff = coeff * scene->lights->intensity;
			res_color = add_color(res_color, shad_color(*f_color, multip_color(tmp_light->color, coeff)));
			res_color = add_color(res_color, phong.specular);
		}
		tmp_light = tmp_light->next;
	}
	return (res_color);
}

s_phong		calc_phong(s_vector intersec_point, s_scene *scene, s_vector normal)
{
	s_phong	phong;

	phong.intersec_point = intersec_point;
	phong.light_dir = subs_vectors(scene->lights->coordinates, intersec_point);
	phong.light_dir = vector_normalise(phong.light_dir);
	phong.view_dir = subs_vectors(scene->cams->coordinates, intersec_point);
	phong.view_dir = vector_normalise(phong.view_dir);
	phong.halfway_dir = add_vectors(phong.light_dir, phong.view_dir);
	phong.halfway_dir = vector_normalise(phong.halfway_dir);
	phong.spec = pow(MAX(vector_scalar_mult(normal, phong.halfway_dir), 0.0), SHININESS);
	phong.specular = multip_color(multip_color(scene->lights->color, scene->lights->intensity), phong.spec);
	return (phong);
}

s_color		shad_color(s_color figur, s_color ab_light)
{
	s_color	res;

	res.r = figur.r * ab_light.r * COLOR_COEFF;
	res.g = figur.g * ab_light.g * COLOR_COEFF;
	res.b = figur.b * ab_light.b * COLOR_COEFF;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	return (res);
}

s_color		final_color(float coeff, s_color color, s_lights *light)
{
	s_color tmp;

	tmp = multip_color(light->color, coeff);
	if (tmp.r > 255)
		tmp.r = 255;
	if (tmp.g > 255)
		tmp.g = 255;
	if (tmp.b > 255)
		tmp.b = 255;
	tmp = normal_color(mult_color_by_color(tmp, color));
	return (tmp);
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

int			shadow_intersec(s_vec_fig *figures, s_lights *lights, s_vector *intersec_point, s_vector *dir_to_light)
{
	int				len = figures->length;
	s_lights		*light_tmp;
	s_figures		*node;
	s_ray			ray;
	float 			res;
	float			x_one;
	int				i;

	i = 0;
	node = figures->node;
	light_tmp = lights;
	ray.orig = *(intersec_point);
	ray.dir = vector_normalise(*(dir_to_light));
	i = 0;
	x_one = vector_length(*dir_to_light);
	while (i < len)
	{
		if (node[i].specif == S_SP)
		{
			res = sphere_intersect(ray, (s_sphere*)node[i].content);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		else if (node[i].specif == S_TR)
		{
			res = triangle_intersec(&ray, (s_triangle*)node[i].content);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		else if (node[i].specif == S_SQ)
		{
			res = square_intersec(ray, (s_square*)node[i].content, x_one);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		++i;
	}
	return (0);
}

float			sphere_intersect(s_ray ray, s_sphere *sp)
{
	float		b;
	float		c;
	float		discr;
	float		x_one;
	s_vector	res;

	x_one = 0;
	res = subs_vectors(ray.orig, sp->coordinates);
	b = 2 * vector_scalar_mult(res, ray.dir);
	c = vector_scalar_mult(res, res) - (sp->radius * sp->radius);
	discr = (b * b) - (4 * c);
	if (discr < 0)
		return (0);
	x_one = (-b - sqrt(discr)) * 0.5;
	//float x_two = (-b + sqrt(discr)) / 2;
	// printf("solved with [%.3f %.3f]\n", x_one, x_two);
//	printf("%f\n", x_one);
	if (x_one > 0)
		return (x_one);
	return (0);
}

float			plane_intersect(s_ray ray, s_plane *plane)
{
	float denom = vector_scalar_mult(plane->normal, ray.dir);
	s_vector tmp;
	if (ABS(denom) > MIN_I)
	{
		tmp = subs_vectors(plane->coordinates, ray.orig);
		float t = vector_scalar_mult(tmp, plane->normal) / denom;
		if (t > 0)
			return t;
	}
	return (0);
}

float			triangle_intersec(s_ray *ray, s_triangle *triangle)
{
	s_vector	pvec = cross_prod(triangle->ac, ray->dir);
	float		det = vector_scalar_mult(triangle->ab, pvec);
	float		inv_det;

	if (det < MIN_I && det > MIN_I)
		return (0);
	inv_det = 1.0 / det;
	s_vector tvec = subs_vectors(ray->orig, triangle->a);
	float u = vector_scalar_mult(tvec, pvec) * inv_det;
	if (u < 0 || u > 1)
		return (0);
	s_vector qvec = cross_prod(triangle->ab, tvec);
	float v = vector_scalar_mult(ray->dir, qvec) * inv_det;
	if (v < 0 || u + v > 1)
		return (0);
	return (vector_scalar_mult(triangle->ac, qvec) * inv_det);
}

float			square_intersec(s_ray ray, s_square *sq, float min_t)
{
	float		denom;
	float		t;
	s_vector	hit_point;
	s_vector	p0l0;
	float		half;

	half = sq->side * 0.5;
	denom = vector_scalar_mult(sq->normal, ray.dir);
	if (ABS(denom) > MIN_I)
	{
		p0l0 = subs_vectors(sq->center, ray.orig);
		t = vector_scalar_mult(p0l0, sq->normal) / denom;
		hit_point = add_vectors(ray.orig, vector_by_scalar(ray.dir, t));
		if (ABS(t) >= 0)
		{
			if (ABS(hit_point.v_x - sq->center.v_x) > half)
				return (0);
			if (ABS(hit_point.v_y - sq->center.v_y) > half)
				return (0);
			if (ABS(hit_point.v_z - sq->center.v_z) > half)
				return (0);
			else
				return (t);
		}
	}
	return (0);
}

// float			cy_intersect(s_ray *ray, s_sphere *sp)
// {

// }

s_color	multip_color(s_color color, float coeff)
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

s_color	add_color(s_color color, s_color color_s)
{
	color.r = color.r + color_s.r;
	if (color.r >= 255)
		color.r = 255;
	color.g = color.g + color_s.g;
	if (color.g >= 255)
		color.g = 255;
	color.b = color.b + color_s.b;
	if (color.b >= 255)
		color.b = 255;
	return (color);
}
