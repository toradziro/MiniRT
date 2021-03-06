/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/06 22:29:50 by ehillman         ###   ########.fr       */
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
			if (intersec < min && intersec > 0.000001)
			{
				sphere_tmp = (s_sphere*)tmp[i].content;
				min = intersec;
				s_vector	intersec_point = vector_by_scalar(ray.dir, min);
				intersec_point = add_vectors(intersec_point, scene->cams->coordinates);
				s_vector normal = subs_vectors(intersec_point, sphere_tmp->coordinates);
				normal = vector_normalise(normal);
				c_tmp = find_color(scene, &ray, min, normal, sphere_tmp->color);
			}
		}
		else if (tmp[i].specif == S_PL)
		{
			intersec = plane_intersect(ray, (s_plane*)tmp[i].content);
			if (intersec < min && intersec > 0.000001)
			{
				plane_tmp = (s_plane*)tmp[i].content;
				// if (vector_scalar_mult(scene->cams->direction, plane_tmp->normal) < 0)
				// 	plane_tmp->normal = vector_by_scalar(plane_tmp->normal, -1.0);
				min = intersec;
				c_tmp = find_color(scene, &ray, min, plane_tmp->normal, plane_tmp->color);
			}
		}
		else if (tmp[i].specif == S_TR)
		{
			intersec = triangle_intersec(&ray, (s_triangle*)tmp[i].content);
			if (intersec < min && intersec > 0.000001)
			{
				s_triangle *triangle_tmp = (s_triangle*)tmp[i].content;
				min = intersec;
				c_tmp = find_color(scene, &ray, min, triangle_tmp->normal, triangle_tmp->color);
			}
		}
		else if (tmp[i].specif == S_SQ)
		{
			intersec = square_intersec(ray, (s_square*)tmp[i].content, min);
			if (intersec < min && intersec > 0.000001)
			{
				s_square *square_tmp = (s_square*)tmp[i].content;
				min = intersec;
				c_tmp = find_color(scene, &ray, min, square_tmp->normal, square_tmp->color);
			}
		}
		++i;
	}
	return (c_tmp);
}

s_color			find_color(s_scene *scene, s_ray *ray, float min, s_vector normal, s_color f_color)
{
	s_vector	intersec_point;
	float		coeff;
	s_color		res_color;
	s_color		tmp_color;
	s_phong		phong;
	s_vector	dir_to_light;
	s_lights	*tmp_light;

	tmp_light = scene->lights;
	intersec_point = vector_by_scalar(ray->dir, min);
	intersec_point = add_vectors(intersec_point, ray->orig);
	res_color = shad_color(f_color, scene->ab_light->color);
	while (tmp_light)
	{
		dir_to_light = subs_vectors(tmp_light->coordinates, intersec_point);
		dir_to_light = vector_normalise(dir_to_light);
		if (!(shadow_intersec(scene->figures, tmp_light, &intersec_point, &dir_to_light)))
		{
			phong = calc_phong(intersec_point, scene, normal);
			coeff = vector_scalar_mult(normal, dir_to_light);
			if (coeff < 0)
				coeff = 0;
			coeff = coeff * scene->lights->intensity;
			res_color = add_color(res_color, shad_color(f_color, multip_color(tmp_light->color, coeff)));
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

s_color		final_color(float coeff, s_color color, s_lights *light, s_phong phong)
{
	s_color	tmp_res = {0, 0, 0};
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
//	static s_figures	*last_intersec;

	i = 0;
	node = figures->node;
	light_tmp = lights;
	ray.orig = *(intersec_point);
	ray.dir = *(dir_to_light);
	//while (light_tmp)
	//{
		i = 0;
		x_one = vector_length(*intersec_point);
		while (i < len)
		{
			if (node[i].specif == S_SP)
			{
				res = sphere_intersect(ray, (s_sphere*)node[i].content);
				if (res < x_one && res > 0.000001)
				{
//					last_intersec = &node[i];
					return (1);
				}
			}
			else if (node[i].specif == S_TR)
			{
				res = triangle_intersec(&ray, (s_triangle*)node[i].content);
				if (res < x_one && res > 0.000001)
				{
//					last_intersec = &node[i];
					return (1);
				}
			}
			else if (node[i].specif == S_SQ)
			{
				res = square_intersec(ray, (s_square*)node[i].content, x_one);
				if (res < x_one && res > 0.000001)
				{
//					last_intersec = &node[i];
					return (1);
				}
			}
			++i;
		}
	//	}
	//	light_tmp = light_tmp->next;
	//}
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
	float		denom = vector_scalar_mult(plane->normal, ray.dir);
	float		t;

	if (denom > 0.01 || -denom > 0.01)
	{
		s_vector p0l0 = subs_vectors(plane->coordinates, ray.orig);
		t = vector_scalar_mult(p0l0, plane->normal);
		if (t >= 0)
			return (t / denom);
	}
	return (0);
}

float			triangle_intersec(s_ray *ray, s_triangle *triangle)
{
	s_vector	pre_det;
	s_vector	tvec;
	s_vector	qvec;
	float		u;
	float		v;
	float		t;
	float		deter;
	float		inv_deter;

	pre_det = cross_prod(ray->dir, triangle->ac);
	deter = vector_scalar_mult(triangle->ab, pre_det);
	if (deter > 0.01)
		return (0);
	inv_deter = 1.0 / deter;
	tvec = subs_vectors(ray->orig, triangle->a);
	u = vector_scalar_mult(tvec, pre_det) * inv_deter;
	if (u < 0.0 || u > 1.0)
		return (0);
	qvec = cross_prod(tvec, triangle->ab);
	v = vector_scalar_mult(ray->dir, qvec) * inv_deter;
	if (v < 0.0 || u + v > 1.0)
		return (0);
	t = vector_scalar_mult(triangle->ac, qvec) * inv_deter;
	return (t);
}

float			square_intersec(s_ray ray, s_square *sq, float min_t)
{
	s_cam_to_w	b;
	s_vector	a_new;
	s_vector	intersec_point;
	s_vector	a_p;
	float		res;
	float		dot;

	if ((res = plane_intersect(ray, (s_plane*)sq)) < min_t)
	{
		b = matrix_place(new_vector(0, 0, 0), sq->normal);
		intersec_point = vector_by_scalar(ray.dir, res);
		a_new = subs_vectors(sq->center, ray.orig);
		a_new = matrix_mult(a_new, b);
		intersec_point = matrix_mult(intersec_point, b);
		intersec_point = add_vectors(a_new, intersec_point);
		a_new = add_vectors(a_new, a_new);
		a_p = subs_vectors(a_new, intersec_point);
		dot = vector_scalar_mult(a_p, new_vector(b.matrix[1][0], b.matrix[1][1], b.matrix[1][2]));
		if (dot >= -sq->side * 0.5 && dot <= sq->side * 0.5)
		{
			dot = vector_scalar_mult(a_p, new_vector(b.matrix[0][0], b.matrix[0][1], b.matrix[0][2]));
			if (dot >= -sq->side * 0.5 && dot <= sq->side * 0.5)
				return (res);
		}
	}
	return (min_t);
}

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
