/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 18:38:54 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_color			intersec(t_scene *scene, t_ray ray)
{
	t_color			c_tmp;
	t_figures		*tmp;
	float			min;
	int				i;
	int				finish;

	i = 0;
	tmp = scene->figures->node;
	finish = scene->figures->length;
	min = MAX_INTERSEC;
	while (i < finish)
	{
		if (&tmp[i])
			ray_switch(&tmp[i], scene, &min, ray, &c_tmp);
		if (&tmp[i + 1])
			ray_switch(&tmp[i + 1], scene, &min, ray, &c_tmp);
		if (&tmp[i + 2])
			ray_switch(&tmp[i + 2], scene, &min, ray, &c_tmp);
		if (&tmp[i + 3])
			ray_switch(&tmp[i + 3], scene, &min, ray, &c_tmp);
		i += 4;
	}
	return (c_tmp);
}

void			ray_switch(t_figures *tmp, t_scene *scene,
				float *min, t_ray ray, t_color *c_tmp)
{
	if (tmp->specif == S_TR)
		triangle_start(scene, tmp->content, min, ray, c_tmp);
	else if (tmp->specif == S_SP)
		sphere_start(scene, tmp->content, min, ray, c_tmp);
	else if (tmp->specif == S_PL)
		plane_start(scene, tmp->content, min, ray, c_tmp);
	else if (tmp->specif == S_SQ)
		sq_start(scene, tmp->content, min, ray, c_tmp);
	else if (tmp->specif == S_CL)
		cy_start(scene, tmp->content, min, ray, c_tmp);
}

t_color			find_color(t_scene *scene, t_ray ray, float min,
				t_vector *normal, t_color *f_color)
{
	t_vector	intersec_point;
	t_vector	dir_to_light;
	t_lights	*tmp_light;
	float		coeff;
	t_phong		phong;
	t_color		ret_color;
	t_color		tmp_color;

	dir_to_light = new_vector(0, 0, 0);
	tmp_light = scene->lights;
	intersec_point = vector_by_scalar(ray.dir, min);
	intersec_point = add_vectors(intersec_point, ray.orig);
	ret_color = shad_color(f_color, &scene->ab_light->color);
	while (tmp_light)
	{
		dir_to_light = subs_vectors(tmp_light->coordinates, intersec_point);
		if (!(shadow_intersec(scene->figures, &intersec_point, &dir_to_light)))
		{
			dir_to_light = vector_normalise(dir_to_light);
			coeff = vector_scalar_mult(*(normal), dir_to_light);
			if (coeff < 0)
				coeff = 0;
			coeff = coeff * tmp_light->intensity;
			tmp_color = multip_color(&tmp_light->color, coeff);
			tmp_color = shad_color(f_color, &tmp_color);
			ret_color = add_color(&ret_color, &tmp_color);
			phong = calc_phong(intersec_point, scene, *normal);
			ret_color = add_color(&ret_color, &phong.specular);
		}
		tmp_light = tmp_light->next;
	}
	return (ret_color);
}

t_phong		calc_phong(t_vector intersec_point, t_scene *scene, t_vector normal)
{
	t_phong	phong;

	phong.intersec_point = intersec_point;
	phong.light_dir = subs_vectors(scene->lights->coordinates, intersec_point);
	phong.light_dir = vector_normalise(phong.light_dir);
	phong.view_dir = subs_vectors(scene->cams->coordinates, intersec_point);
	phong.view_dir = vector_normalise(phong.view_dir);
	phong.halfway_dir = add_vectors(phong.light_dir, phong.view_dir);
	phong.halfway_dir = vector_normalise(phong.halfway_dir);
	phong.spec = pow(MAX(vector_scalar_mult(normal,
				phong.halfway_dir), 0.0), SHININESS);
	phong.specular = multip_color(&scene->lights->color,
				scene->lights->intensity);
	phong.specular = multip_color(&phong.specular, phong.spec);
	return (phong);
}

t_color		shad_color(t_color *figur, t_color *ab_light)
{
	t_color	res;

	res.r = figur->r * ab_light->r * COLOR_COEFF;
	res.g = figur->g * ab_light->g * COLOR_COEFF;
	res.b = figur->b * ab_light->b * COLOR_COEFF;
	if (res.r > MAX_COLOR)
		res.r = MAX_COLOR;
	if (res.g > MAX_COLOR)
		res.g = MAX_COLOR;
	if (res.b > MAX_COLOR)
		res.b = MAX_COLOR;
	return (res);
}

int			shadow_intersec(t_vec_fig *figures, t_vector *intersec_point,
							t_vector *dir_to_light)
{
	int				len = figures->length;
	t_figures		*node;
	t_ray			ray;
	float			res;
	float			x_one;
	int				i;

	node = figures->node;
	ray.orig = *(intersec_point);
	ray.dir = vector_normalise(*dir_to_light);
	i = 0;
	x_one = vector_length(*dir_to_light);
	while (i < len)
	{
		if (node[i].specif == S_SP)
		{
			res = sphere_intersect(ray, (t_sphere*)node[i].content);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		else if (node[i].specif == S_TR)
		{
			res = triangle_intersec(ray, (t_triangle*)node[i].content);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		else if (node[i].specif == S_SQ)
		{
			res = square_intersec(ray, (t_square*)node[i].content, x_one);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		else if (node[i].specif == S_PL)
		{
			res = plane_intersect(ray, node[i].content);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		else if (node[i].specif == S_CL)
		{
			res = cy_intersect(ray, node[i].content);
			if (res < x_one && res > MIN_I)
				return (1);
		}
		++i;
	}
	return (0);
}

float			sphere_intersect(t_ray ray, t_sphere *sp)
{
	float		b;
	float		c;
	float		discr;
	float		x_one;
	float		x_two;
	t_vector	res;

	if (sp)
	{
		res = subs_vectors(ray.orig, sp->coordinates);
		b = 2 * vector_scalar_mult(res, ray.dir);
		c = vector_scalar_mult(res, res) - (sp->radius * sp->radius);
		discr = (b * b) - (4 * c);
		if (discr < 0)
			return (0);
		x_one = (-b - sqrt(discr)) * 0.5;
		x_two = (-b + sqrt(discr)) * 0.5;
		if (x_one > MIN_I && x_two > MIN_I)
			return (MIN(x_one, x_two));
		if (x_one > MIN_I || x_two > MIN_I)
			return (MAX(x_one, x_two));
	}
	return (0);
}

float			plane_intersect(t_ray ray, t_plane *plane)
{
	float denom;
	t_vector tmp;

	denom = vector_scalar_mult(plane->normal, ray.dir);
	if (ABS(denom) > MIN_I)
	{
		tmp = subs_vectors(plane->coordinates, ray.orig);
		float t = vector_scalar_mult(tmp, plane->normal) / denom;
		if (t > 0)
			return t;
	}
	return (0);
}

float			triangle_intersec(t_ray ray, t_triangle *triangle)
{
	t_vector	pvec;
	t_vector	tvec;
	float		u;
	float		det;
	float		inv_det;
	t_vector	qvec;
	float		v;

	pvec = cross_prod(triangle->ac, ray.dir);
	det = vector_scalar_mult(triangle->ab, pvec);
	if (det == 0)
		return (0);
	inv_det = 1.0 / det;
	tvec = subs_vectors(ray.orig, triangle->a);
	u = vector_scalar_mult(tvec, pvec) * inv_det;
	if (u < 0 || u > 1)
		return (0);
	qvec = cross_prod(triangle->ab, tvec);
	v = vector_scalar_mult(ray.dir, qvec) * inv_det;
	if (v < 0 || u + v > 1)
		return (0);
	v = vector_scalar_mult(triangle->ac, qvec) * inv_det;
	if (v > MIN_I)
		return (v);
	return (0);
}

float			square_intersec(t_ray ray, t_square *sq, float min_t)
{
	t_cam_to_w	b;
	t_vector	intersec_point;
	t_vector	a_p;
	float		res;
	float		tmp_1;
	float		tmp_2;

	min_t = 0;
	res = 0;
	if ((res = plane_intersect(ray, (t_plane*)sq)) > 0)
	{
		intersec_point = vector_by_scalar(ray.dir, res);
		intersec_point = add_vectors(intersec_point, ray.orig);
		a_p = subs_vectors(intersec_point, sq->center);
		b = matrix_place(sq->center, sq->normal);
		tmp_1 = vec_matrix_mult_first_row(a_p, b);
		tmp_2 = vec_matrix_mult_second_row(a_p, b);
		if ((ABS(tmp_1) > sq->side * 0.5) || (ABS(tmp_2) > sq->side * 0.5))
			return (0);
	}
	return (res);
}

float			cy_intersect(t_ray ray, t_cylinder *cy)
{
	t_vector	co;
	t_vector	ap_one;
	t_vector	ap_two;
	float		d_one;
	float		d_two;
	float		a;
	float		b;
	float		c;
	float		det;
	float		x_one;
	float		x_two;

	if (cy)
	{
		co = subs_vectors(ray.orig, cy->coordinates);
		a = -(pow(vector_scalar_mult(ray.dir, cy->axis), 2) - 1);
		b = -(2 * (vector_scalar_mult(co, cy->axis) *
				vector_scalar_mult(ray.dir, cy->axis) -
				vector_scalar_mult(ray.dir, co)));
		c = +(vector_scalar_mult(co, co) -
				pow(vector_scalar_mult(cy->axis, co), 2) -
				pow(cy->diameter * 0.5, 2));
		det = b * b - 4 * a * c;
		if (det < 0)
			return (0);
		x_one = (-b - sqrt(det)) / (2 * a);
		x_two = (-b + sqrt(det)) / (2 * a);
		ap_one = vector_by_scalar(cy->axis, x_one);
		ap_two = vector_by_scalar(cy->axis, x_two);
		d_one = vector_scalar_mult(ray.dir, ap_one) +
				vector_scalar_mult(co, cy->axis);
		d_two = vector_scalar_mult(ray.dir, ap_two) +
				vector_scalar_mult(co, cy->axis);
		if (ABS(d_one) >= cy->height / 2)
			x_one = -1;
		if (ABS(d_two) >= cy->height / 2)
			x_two = -1;
		if (x_one > MIN_I && x_two > MIN_I)
			return (MIN(x_one, x_two));
		if (x_one > MIN_I || x_two > MIN_I)
			return (MAX(x_one, x_two));
	}
	return (0);
}

t_vector		find_cy_normal(float intersec, t_cylinder cy, t_ray ray)
{
	t_vector	intersec_point;
	t_vector	cp;
	t_vector	t;
	t_vector	normal;

	intersec_point = vector_by_scalar(ray.dir, intersec);
	intersec_point = add_vectors(ray.orig, intersec_point);
	cp = subs_vectors(intersec_point, cy.coordinates);
	t = cross_prod(cp, cy.axis);
	normal = cross_prod(t, cy.axis);
	return (normal);
}

t_color	multip_color(t_color *color, float coeff)
{
	t_color		res;

	res.r = coeff * color->r;
	if (res.r >= 255)
		res.r = 255;
	res.g = coeff * color->g;
	if (res.g >= 255)
		res.g = 255;
	res.b = coeff * color->b;
	if (res.b >= 255)
		res.b = 255;
	return (res);
}

t_color	add_color(t_color *color, t_color *color_s)
{
	color->r = color->r + color_s->r;
	if (color->r >= 255)
		color->r = 255;
	color->g = color->g + color_s->g;
	if (color->g >= 255)
		color->g = 255;
	color->b = color->b + color_s->b;
	if (color->b >= 255)
		color->b = 255;
	return (*color);
}
