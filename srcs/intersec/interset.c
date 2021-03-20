#include "../includes/MiniRT.h"

void			sphere_start(t_scene *scene, t_sphere *sp, float *min, t_ray ray, t_color *c_tmp)
{
	t_sphere	*sphere_tmp;
	t_vector	intersec_point;
	t_vector	normal;
	float		intersec;

	intersec = sphere_intersect(ray, sp);
	sphere_tmp = sp;
	if (intersec < *(min) && intersec > MIN_I)
	{
		*(min) = intersec;
		intersec_point = vector_by_scalar(ray.dir, *(min));
		intersec_point = add_vectors(intersec_point, scene->cams->coordinates);
		normal = subs_vectors(intersec_point, sphere_tmp->coordinates);
		normal = vector_normalise(normal);
		*(c_tmp) = find_color(scene, ray, *(min), &normal, &sphere_tmp->color);
	}
}

void 			plane_start(t_scene *scene, t_plane *pl, float *min, t_ray ray, t_color *c_tmp)
{
	t_plane		*plane_tmp;
	float		intersec;

	plane_tmp = pl;
	intersec = plane_intersect(ray, plane_tmp);
	if (intersec < *(min) && intersec > MIN_I)
	{
		if (vector_scalar_mult(ray.dir, plane_tmp->normal) > 0)
			plane_tmp->normal = vector_by_scalar(plane_tmp->normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, *(min), &plane_tmp->normal, &plane_tmp->color);
	}
}

void 			triangle_start(t_scene *scene, t_triangle *tr, float *min, t_ray ray, t_color *c_tmp)
{
	float		intersec;
	t_triangle *triangle_tmp;
	t_vector	normal;

	triangle_tmp = tr;
	normal = triangle_tmp->normal;
	intersec = triangle_intersec(ray, tr);
	if (intersec < *(min) && intersec > MIN_I)
	{
		if (vector_scalar_mult(ray.dir, normal) > 0)
			normal = vector_by_scalar(normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, *(min), &normal, &triangle_tmp->color);
	}
}

void 		sq_start(t_scene *scene, t_square *sq, float *min, t_ray ray, t_color *c_tmp)
{
	float	intersec;
	t_square *square_tmp;

	square_tmp = sq;
	intersec = square_intersec(ray, square_tmp, *(min));
	if (intersec < *(min) && intersec > MIN_I)
	{
		if (vector_scalar_mult(ray.dir, square_tmp->normal) > 0)
			square_tmp->normal = vector_by_scalar(square_tmp->normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, *(min),
					&square_tmp->normal, &square_tmp->color);
	}
}

void 		cy_start(t_scene *scene, t_cylinder *cy,
			float *min, t_ray ray, t_color *c_tmp)
{
	float		intersec;
	t_vector	normal;

	intersec = cy_intersect(ray, cy);
	if (intersec < *(min) && intersec > MIN_I)
	{
		normal = find_cy_normal(intersec, *cy, ray);
		normal = vector_normalise(normal);
		if (vector_scalar_mult(ray.dir, normal) > 0)
			normal = vector_by_scalar(normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, intersec, &normal, &cy->color);
	}
}
