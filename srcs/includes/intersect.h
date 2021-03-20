/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:07 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:10:08 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_INTERSECT_H
# define MINIRT_INTERSECT_H

void			sphere_start(t_scene *scene, t_sphere *sp,
				float *min, t_ray ray, t_color *c_tmp);
void			plane_start(t_scene *scene, t_plane *pl,
				float *min, t_ray ray, t_color *c_tmp);
void			triangle_start(t_scene *scene, t_triangle
				*tr, float *min, t_ray ray, t_color *c_tmp);
void			sq_start(t_scene *scene, t_square *sq,
				float *min, t_ray ray, t_color *c_tmp);
void			cy_start(t_scene *scene, t_cylinder *cy,
				float *min, t_ray ray, t_color *c_tmp);
t_vector		find_cy_normal(float intersec, t_cylinder cy, t_ray ray);
float			sphere_intersect(t_ray ray, t_sphere *sp);
float			plane_intersect(t_ray ray, t_plane *plane);
float			triangle_intersec(t_ray ray, t_triangle *triangle);
float			square_intersec(t_ray ray, t_square *sq, float min_t);
float			cy_intersect(t_ray ray, t_cylinder *cy);

#endif
