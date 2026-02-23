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

#include "../random/random.h"
#include "ray_trace.h"
#include <math.h>
#include <time.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define MIN_I 0.004
#define MAX_INTERSEC 100000

#define SHININESS 100.0
#define COLOR_COEFF 0.003921568627

#define MAX_COLOR 255

typedef struct s_hit
{
    t_triangle* triangle;
    t_vector    normal;
    float       t;
} t_hit;

void swap(float* a, float* b)
{
    float tmp = *a;
    *a        = *b;
    *b        = tmp;
}

bool intersectAABB(t_BVHNode* currNode, t_ray* ray, float closest)
{
    float t_min_x = (currNode->aabb.min.v_x - ray->orig.v_x) / ray->dir.v_x;
    float t_max_x = (currNode->aabb.max.v_x - ray->orig.v_x) / ray->dir.v_x;
    if (ray->dir.v_x < 0)
    {
        swap(&t_min_x, &t_max_x);
    }

    float t_min_y = (currNode->aabb.min.v_y - ray->orig.v_y) / ray->dir.v_y;
    float t_max_y = (currNode->aabb.max.v_y - ray->orig.v_y) / ray->dir.v_y;
    if (ray->dir.v_y < 0)
    {
        swap(&t_min_y, &t_max_y);
    }

    float t_min_z = (currNode->aabb.min.v_z - ray->orig.v_z) / ray->dir.v_z;
    float t_max_z = (currNode->aabb.max.v_z - ray->orig.v_z) / ray->dir.v_z;
    if (ray->dir.v_z < 0)
    {
        swap(&t_min_z, &t_max_z);
    }

    float lastHit     = MAX(MAX(t_min_x, t_min_y), t_min_z);
    float firstPassed = MIN(MIN(t_max_x, t_max_y), t_max_z);

    if (lastHit > closest || firstPassed < 0.0f)
    {
        return false;
    }

    return lastHit <= firstPassed;
}

t_hit traverseBVH(t_scene* scene, t_ray* ray, float min, bool stop_on_first)
{
    t_BVHNode* nodes[100];
    memset(nodes, 0, sizeof(t_BVHNode*) * 100);

    nodes[0]      = scene->bvh.root;
    int stackSize = 1;

    t_hit res = {NULL, {0, 0, 0}, 0};

    while (stackSize > 0)
    {
        --stackSize;
        t_BVHNode* currNode = nodes[stackSize];
        if (intersectAABB(currNode, ray, min))
        {
            if (currNode->is_leaf)
            {
                for (int i = 0; i < currNode->count; ++i)
                {
                    float    intersec = triangle_intersec(*ray, &currNode->batch[i]);
                    t_vector normal   = currNode->batch[i].normal;

                    if (intersec < min && intersec > MIN_I)
                    {
                        if (vector_scalar_mult(&ray->dir, &normal) > 0)
                        {
                            normal = vector_by_scalar(&normal, -1);
                        }
                        min          = intersec;
                        res.normal   = normal;
                        res.triangle = &currNode->batch[i];
                        res.t        = intersec;
                        if (stop_on_first)
                        {
                            return res;
                        }
                    }
                }
            }
            else
            {
                if (currNode->left != NULL)
                {
                    nodes[stackSize] = currNode->left;
                    ++stackSize;
                }
                if (currNode->right != NULL)
                {
                    nodes[stackSize] = currNode->right;
                    ++stackSize;
                }
            }
        }
    }
    return res;
}

t_color mix_colors(t_color a, t_color b, float reflection_value)
{
    a.r = a.r * (1.0f - reflection_value) + b.r * reflection_value;
    a.g = a.g * (1.0f - reflection_value) + b.g * reflection_value;
    a.b = a.b * (1.0f - reflection_value) + b.b * reflection_value;
    return a;
}

void add_roughness(t_vector* vec, float roughness)
{
    t_vector coef_vec = {2.0f, 2.0f, 2.0f};
    coef_vec.v_x      = 2.0f * rng_float(&thread_local_rng) - 1.0f;
    coef_vec.v_y      = 2.0f * rng_float(&thread_local_rng) - 1.0f;
    coef_vec.v_z      = 2.0f * rng_float(&thread_local_rng) - 1.0f;
    coef_vec          = vector_normalize(&coef_vec);
    coef_vec          = vector_by_scalar(&coef_vec, roughness);
    *vec              = add_vectors(vec, &coef_vec);
    *vec              = vector_normalize(vec);
}

t_color reflect(t_scene* scene, t_ray* ray, t_hit* hit, int reflect_depth)
{
    float    dot_product   = vector_scalar_mult(&ray->dir, &hit->normal);        // d · n
    t_vector scaled_normal = vector_by_scalar(&hit->normal, 2.0f * dot_product); // 2 * (d · n) * n
    t_vector reflected_v   = subs_vectors(&ray->dir, &scaled_normal);

    t_ray       reflected_ray;
    const float epsilon    = 0.001f;
    reflected_ray.orig.v_x = ray->orig.v_x + hit->t * ray->dir.v_x + epsilon * hit->normal.v_x;
    reflected_ray.orig.v_y = ray->orig.v_y + hit->t * ray->dir.v_y + epsilon * hit->normal.v_y;
    reflected_ray.orig.v_z = ray->orig.v_z + hit->t * ray->dir.v_z + epsilon * hit->normal.v_z;
    reflected_ray.dir      = reflected_v;
    if (scene->roughness_and_multisample)
    {
        add_roughness(&reflected_ray.dir, scene->roughness_val);
    }

    float min           = MAX_INTERSEC;
    t_hit reflected_hit = traverseBVH(scene, &reflected_ray, min, false);
    if (reflected_hit.triangle)
    {
        t_color reflected_color =
            find_color(scene, reflected_ray, reflected_hit.t, &reflected_hit.normal, &reflected_hit.triangle->color);
        if (reflected_hit.triangle->reflection_value != 0 && reflect_depth > 0)
        {
            t_color recursive_reflection = reflect(scene, &reflected_ray, &reflected_hit, reflect_depth - 1);
            reflected_color =
                mix_colors(reflected_color, recursive_reflection, reflected_hit.triangle->reflection_value);
        }

        return reflected_color;
    }
    return scene->ab_light->color;
}

t_color* accumulative_multisampling(t_accum_data* accum, t_color* base_color)
{
    if (accum->count == 0)
    {
        accum->med_color = *base_color;
        ++accum->count;
    }
    else
    {
        ++accum->count;
        const float delta_r = (base_color->r - accum->med_color.r) / accum->count;
        const float delta_g = (base_color->g - accum->med_color.g) / accum->count;
        const float delta_b = (base_color->b - accum->med_color.b) / accum->count;

        accum->med_color.r += delta_r;
        accum->med_color.g += delta_g;
        accum->med_color.b += delta_b;
    }
    return &accum->med_color;
}

t_color ray_trace(t_scene* scene, t_ray ray, i32 x, i32 y)
{
    if (thread_local_rng.state == 0)
    {
        thread_local_rng.state = (unsigned int)time(NULL) + (ray.orig.v_x + 40) * 1234;
    }
    t_color base_color = scene->ab_light->color;
    float   min        = MAX_INTERSEC;

    t_hit hit = traverseBVH(scene, &ray, min, false);
    if (hit.triangle)
    {
        base_color = find_color(scene, ray, hit.t, &hit.normal, &hit.triangle->color);
        if (hit.triangle->reflection_value != 0)
        {
            base_color = mix_colors(base_color, reflect(scene, &ray, &hit, 4), hit.triangle->reflection_value);
        }
    }
    //-- Real-time multisampling
    if (scene->roughness_and_multisample)
    {
        t_accum_data* accum = scene->pixels_avg + (y * scene->width) + x;
        base_color          = *accumulative_multisampling(accum, &base_color);
    }
    return base_color;
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
    intersec_point = vector_by_scalar(&ray.dir, min);
    intersec_point = add_vectors(&intersec_point, &ray.orig);
    ret_color      = shad_color(f_color, &scene->ab_light->color);
    while (tmp_light)
    {
        dir_to_light      = subs_vectors(&tmp_light->coordinates, &intersec_point);
        dir_to_light_norm = vector_normalize(&dir_to_light);
        coeff             = vector_scalar_mult(normal, &dir_to_light_norm);
        if (coeff <= 0.0f)
        {
            tmp_light = tmp_light->next;
            continue;
        }
        if (shadow_intersec(scene, &intersec_point, &dir_to_light))
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
    phong.light_dir      = subs_vectors(&scene->lights->coordinates, &intersec_point);
    phong.light_dir      = vector_normalize(&phong.light_dir);
    phong.view_dir       = subs_vectors(&scene->cams->coordinates, &intersec_point);
    phong.view_dir       = vector_normalize(&phong.view_dir);
    phong.halfway_dir    = add_vectors(&phong.light_dir, &phong.view_dir);
    phong.halfway_dir    = vector_normalize(&phong.halfway_dir);
    phong.spec           = pow(MAX(vector_scalar_mult(&normal, &phong.halfway_dir), 0.0), SHININESS);
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

int shadow_intersec(t_scene* scene, t_vector* intersec_point, t_vector* dir_to_light)
{
    t_ray ray;
    float x_one;

    ray.orig = *(intersec_point);
    x_one    = vector_length(dir_to_light);
    ray.dir  = vector_by_scalar(dir_to_light, 1 / x_one);

    if (traverseBVH(scene, &ray, x_one, true).triangle)
    {
        return (1);
    }
    return (0);
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

    pvec = cross_prod(&triangle->ac, &ray.dir);
    det  = vector_scalar_mult(&triangle->ab, &pvec);
    if (det == 0)
    {
        return (0);
    }
    inv_det = 1.0 / det;
    tvec    = subs_vectors(&ray.orig, &triangle->a);
    u       = vector_scalar_mult(&tvec, &pvec) * inv_det;
    if (u < 0 || u > 1)
    {
        return (0);
    }
    qvec = cross_prod(&triangle->ab, &tvec);
    v    = vector_scalar_mult(&ray.dir, &qvec) * inv_det;
    if (v < 0 || u + v > 1)
    {
        return (0);
    }
    v = vector_scalar_mult(&triangle->ac, &qvec) * inv_det;
    if (v > MIN_I)
    {
        return (v);
    }
    return (0);
}
