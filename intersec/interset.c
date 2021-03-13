#include "../includes/MiniRT.h"

void			sphere_start(s_scene *scene, s_sphere *sp, float *min, s_ray *ray, s_color *c_tmp)
{
	s_sphere	*sphere_tmp;
	s_vector	intersec_point;
	s_vector	normal;
	float		intersec;

	intersec = sphere_intersect(ray, sp);
	sphere_tmp = sp;
	if (intersec < *(min) && intersec > MIN_I)
	{
		*(min) = intersec;
		intersec_point = vector_by_scalar(&ray->dir, *(min));
		intersec_point = add_vectors(&intersec_point, &scene->cams->coordinates);
		normal = subs_vectors(&intersec_point, &sphere_tmp->coordinates);
		normal = vector_normalise(&normal);
		*(c_tmp) = find_color(scene, ray, *(min), &normal, &sphere_tmp->color);
	}
}

void 			plane_start(s_scene *scene, s_plane *pl, float *min, s_ray *ray, s_color *c_tmp)
{
	s_plane		*plane_tmp;
	float		intersec;

	plane_tmp = pl;
	intersec = plane_intersect(ray, plane_tmp);
	if (intersec < *(min) && intersec > MIN_I)
	{
		if (vector_scalar_mult(&ray->dir, &plane_tmp->normal) > 0)
			plane_tmp->normal = vector_by_scalar(&plane_tmp->normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, *(min), &plane_tmp->normal, &plane_tmp->color);
	}
}

void 			triangle_start(s_scene *scene, s_triangle *tr, float *min, s_ray *ray, s_color *c_tmp)
{
	float		intersec;
	s_triangle *triangle_tmp;

	triangle_tmp = tr;
	intersec = triangle_intersec(ray, tr);
	if (intersec < *(min) && intersec > MIN_I)
	{
		if (vector_scalar_mult(&ray->dir, &triangle_tmp->normal) > 0)
			triangle_tmp->normal = vector_by_scalar(&triangle_tmp->normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, *(min), &triangle_tmp->normal, &triangle_tmp->color);
	}
}

void 		sq_start(s_scene *scene, s_square *sq, float *min, s_ray *ray, s_color *c_tmp)
{
	float	intersec;
	s_square *square_tmp;

	square_tmp = sq;
	intersec = square_intersec(ray, square_tmp, *(min));
	if (intersec < *(min) && intersec > MIN_I)
	{
		if (vector_scalar_mult(&ray->dir, &square_tmp->normal) > 0)
			square_tmp->normal = vector_by_scalar(&square_tmp->normal, -1);
		*(min) = intersec;
		*(c_tmp) = find_color(scene, ray, *(min), &square_tmp->normal, &square_tmp->color);
	}
}