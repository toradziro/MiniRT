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

void swap(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
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

    float lastHit = MAX(MAX(t_min_x, t_min_y), t_min_z);
    float firstPassed = MIN(MIN(t_max_x, t_max_y), t_max_z);

    if (lastHit > closest || firstPassed < 0.0f)
    {
        return false;
    }

    return lastHit <= firstPassed;
}

t_color traverseBVH(t_scene* scene, t_ray* ray)
{
    t_BVHNode* nodes[100];
    memset(nodes, 0, sizeof(t_BVHNode*) * 100);
    nodes[0] = scene->bvh.root;
    int stackSize = 1;

    t_color c_tmp = new_color(0, 0, 0);
    float min   = MAX_INTERSEC;

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
                        if (vector_scalar_mult(ray->dir, normal) > 0)
                        {
                            normal = vector_by_scalar(normal, -1);
                        }
                        min   = intersec;
                        c_tmp = find_color(scene, *ray, min, &normal, &currNode->batch[i].color);
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
    return c_tmp;
}

bool traverseBVHHasAnyIntersec(t_scene* scene, t_ray* ray, float min)
{
    t_BVHNode* nodes[100];
    memset(nodes, 0, sizeof(t_BVHNode*) * 100);
    nodes[0] = scene->bvh.root;
    int stackSize = 1;

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
                    if (intersec < min && intersec > MIN_I)
                    {
                        return true;
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
    return false;
}

t_color intersec(t_scene* scene, t_ray ray)
{
    return traverseBVH(scene, &ray);
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

int shadow_intersec(t_scene* scene, t_vector* intersec_point, t_vector* dir_to_light)
{
    t_ray ray;
    float x_one;

    ray.orig = *(intersec_point);
    x_one    = vector_length(*dir_to_light);
    ray.dir  = vector_by_scalar(*dir_to_light, 1 / x_one);
    if (traverseBVHHasAnyIntersec(scene, &ray, x_one))
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
