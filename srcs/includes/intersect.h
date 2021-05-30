#ifndef MINIRT_INTERSECT_H
# define MINIRT_INTERSECT_H

void			sphere_start(t_scene *scene, t_sphere *sp,
				double *min, t_ray ray, t_color *c_tmp);
void			plane_start(t_scene *scene, t_plane *pl,
				double *min, t_ray ray, t_color *c_tmp);
void			triangle_start(t_scene *scene, t_triangle
				*tr, double *min, t_ray ray, t_color *c_tmp);
void			sq_start(t_scene *scene, t_square *sq,
				double *min, t_ray ray, t_color *c_tmp);
void			cy_start(t_scene *scene, t_cylinder *cy,
				double *min, t_ray ray, t_color *c_tmp);
t_vector		find_cy_normal(double intersec, t_cylinder cy, t_ray ray);
double			sphere_intersect(t_ray ray, t_sphere *sp);
double			plane_intersect(t_ray ray, t_plane *plane);
double			triangle_intersec(t_ray ray, t_triangle *triangle);
double			square_intersec(t_ray ray, t_square *sq, double min_t);
double			cy_intersect(t_ray ray, t_cylinder *cy);

#endif
