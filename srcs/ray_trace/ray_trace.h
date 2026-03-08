#pragma once

#include "../includes/figures.h"
#include "../includes/scene.h"

float   triangle_intersec(t_ray ray, t_triangle* triangle);
int     shadow_intersec(t_scene* scene, t_vector* intersec_point, t_vector* dir_to_light);
t_color ray_trace(t_scene* scene, t_ray ray, i32 x, i32 y);
t_color shad_color(t_color* figur, t_color* ab_light);
t_phong calc_phong(t_vector intersec_point, t_scene* scene, t_vector normal);
t_color find_color(t_scene* scene, t_ray ray, float min, t_vector* normal, t_color* f_color);
