#ifndef MINIRT_INTERSECT_H
# define MINIRT_INTERSECT_H

void			sphere_start(s_scene *scene, s_sphere *sp, float *min, s_ray *ray, s_color *c_tmp);
void 			plane_start(s_scene *scene, s_plane *pl, float *min, s_ray *ray, s_color *c_tmp);
void 			triangle_start(s_scene *scene, s_triangle *tr, float *min, s_ray *ray, s_color *c_tmp);
void 			sq_start(s_scene *scene, s_square *sq, float *min, s_ray *ray, s_color *c_tmp);

#endif
