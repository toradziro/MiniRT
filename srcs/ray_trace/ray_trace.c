/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:36:02 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:12:26 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_color intersec(t_scene* scene, t_ray ray)
{
    t_color     c_tmp;
    float       min;

    c_tmp = new_color(0, 0, 0);
    min   = MAX_INTERSEC;
    for (int i = 0; i < scene->figures->length; ++i)
    {
        triangle_start(scene, &scene->figures->triangles[i], &min, ray, &c_tmp);
    }
    return (c_tmp);
}

t_color find_color(t_scene* scene, t_ray ray, float min, t_vector* normal, t_color* f_color)
{
    t_vector  intersec_point;
    t_vector  dir_to_light;
    t_vector  dir_to_light_norm;
    t_lights* tmp_light;
    float     coeff;
    t_phong   phong;
    t_color   ret_color;
    t_color   tmp_color;

    dir_to_light   = new_vector(0, 0, 0);
    tmp_light      = scene->lights;
    intersec_point = vector_by_scalar(ray.dir, min);
    intersec_point = add_vectors(intersec_point, ray.orig);
    ret_color      = shad_color(f_color, &scene->ab_light->color);
    while (tmp_light)
    {
        dir_to_light      = subs_vectors(tmp_light->coordinates, intersec_point);
        dir_to_light_norm = vector_normalise(dir_to_light);
        coeff             = vector_scalar_mult(*normal, dir_to_light_norm);
        if (coeff <= 0.0f)
        {
            tmp_light = tmp_light->next;
            continue;
        }
        if (shadow_intersec(scene->figures, &intersec_point, &dir_to_light))
        {
            tmp_light = tmp_light->next;
            continue;
        }
        coeff     = coeff * tmp_light->intensity;
        tmp_color = multip_color(&tmp_light->color, coeff);
        tmp_color = shad_color(f_color, &tmp_color);
        ret_color = add_color(&ret_color, &tmp_color);
        phong     = calc_phong(intersec_point, scene, *normal);
        ret_color = add_color(&ret_color, &phong.specular);
        tmp_light = tmp_light->next;
    }
    return (ret_color);
}

t_phong calc_phong(t_vector intersec_point, t_scene* scene, t_vector normal)
{
    t_phong phong;

    phong.intersec_point = intersec_point;
    phong.light_dir      = subs_vectors(scene->lights->coordinates, intersec_point);
    phong.light_dir      = vector_normalise(phong.light_dir);
    phong.view_dir       = subs_vectors(scene->cams->coordinates, intersec_point);
    phong.view_dir       = vector_normalise(phong.view_dir);
    phong.halfway_dir    = add_vectors(phong.light_dir, phong.view_dir);
    phong.halfway_dir    = vector_normalise(phong.halfway_dir);
    phong.spec           = pow(MAX(vector_scalar_mult(normal, phong.halfway_dir), 0.0), SHININESS);
    phong.specular       = multip_color(&scene->lights->color, scene->lights->intensity);
    phong.specular       = multip_color(&phong.specular, phong.spec);
    return (phong);
}

t_color shad_color(t_color* figur, t_color* ab_light)
{
    t_color res;

    res.r = figur->r * ab_light->r * COLOR_COEFF;
    res.g = figur->g * ab_light->g * COLOR_COEFF;
    res.b = figur->b * ab_light->b * COLOR_COEFF;
    if (res.r > MAX_COLOR)
    {
        res.r = MAX_COLOR;
    }
    if (res.g > MAX_COLOR)
    {
        res.g = MAX_COLOR;
    }
    if (res.b > MAX_COLOR)
    {
        res.b = MAX_COLOR;
    }
    return (res);
}

int shadow_intersec(t_vec_fig* figures, t_vector* intersec_point, t_vector* dir_to_light)
{
    int   len;
    t_ray ray;
    float res;
    float x_one;
    int   i;

    len      = figures->length;
    ray.orig = *(intersec_point);
    i        = 0;
    x_one    = vector_length(*dir_to_light);
    ray.dir  = vector_by_scalar(*dir_to_light, 1 / x_one);
    while (i < len)
    {
        res = triangle_intersec(ray, &figures->triangles[i]);
        if (res < x_one && res > MIN_I)
        {
            return (1);
        }
        ++i;
    }
    return (0);
}

void triangle_start(t_scene* scene, t_triangle* tr, float* min, t_ray ray, t_color* c_tmp)
{
    float       intersec;
    t_triangle* triangle_tmp;
    t_vector    normal;

    triangle_tmp = tr;
    normal       = triangle_tmp->normal;
    intersec     = triangle_intersec(ray, tr);
    if (intersec < *(min) && intersec > MIN_I)
    {
        if (vector_scalar_mult(ray.dir, normal) > 0)
        {
            normal = vector_by_scalar(normal, -1);
        }
        *(min)   = intersec;
        *(c_tmp) = find_color(scene, ray, *(min), &normal, &triangle_tmp->color);
    }
}

float triangle_intersec(t_ray ray, t_triangle* triangle)
{
    t_vector pvec;
    t_vector tvec;
    float    u;
    float    det;
    float    inv_det;
    t_vector qvec;
    float    v;

    pvec = cross_prod(triangle->ac, ray.dir);
    det  = vector_scalar_mult(triangle->ab, pvec);
    if (det == 0)
    {
        return (0);
    }
    inv_det = 1.0 / det;
    tvec    = subs_vectors(ray.orig, triangle->a);
    u       = vector_scalar_mult(tvec, pvec) * inv_det;
    if (u < 0 || u > 1)
    {
        return (0);
    }
    qvec = cross_prod(triangle->ab, tvec);
    v    = vector_scalar_mult(ray.dir, qvec) * inv_det;
    if (v < 0 || u + v > 1)
    {
        return (0);
    }
    v = vector_scalar_mult(triangle->ac, qvec) * inv_det;
    if (v > MIN_I)
    {
        return (v);
    }
    return (0);
}

t_color multip_color(t_color* color, float coeff)
{
    t_color res;

    res.r = coeff * color->r;
    if (res.r >= 255)
    {
        res.r = 255;
    }
    res.g = coeff * color->g;
    if (res.g >= 255)
    {
        res.g = 255;
    }
    res.b = coeff * color->b;
    if (res.b >= 255)
    {
        res.b = 255;
    }
    return (res);
}

t_color add_color(t_color* color, t_color* color_s)
{
    color->r = color->r + color_s->r;
    if (color->r >= 255)
    {
        color->r = 255;
    }
    color->g = color->g + color_s->g;
    if (color->g >= 255)
    {
        color->g = 255;
    }
    color->b = color->b + color_s->b;
    if (color->b >= 255)
    {
        color->b = 255;
    }
    return (*color);
}
