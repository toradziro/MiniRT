#ifndef MINIRT_INTERSECT_H
# define MINIRT_INTERSECT_H

void			sphere_start(s_scene *scene, s_sphere *sp, float *min, s_ray ray, s_color *c_tmp);
void 			plane_start(s_scene *scene, s_plane *pl, float *min, s_ray ray, s_color *c_tmp);
void 			triangle_start(s_scene *scene, s_triangle *tr, float *min, s_ray ray, s_color *c_tmp);
void 			sq_start(s_scene *scene, s_square *sq, float *min, s_ray ray, s_color *c_tmp);
void			cy_start(s_scene *scene, s_cylinder *cy, float *min, s_ray ray, s_color *c_tmp);
s_vector		find_cy_normal(float intersec, s_cylinder *cy, s_ray ray);
float			sphere_intersect(s_ray ray, s_sphere *sp);
float			plane_intersect(s_ray ray, s_plane *plane);
float			triangle_intersec(s_ray ray, s_triangle *triangle);
float			square_intersec(s_ray ray, s_square *sq, float min_t);
float			cy_intersect(s_ray ray, s_cylinder *cy);

#endif
