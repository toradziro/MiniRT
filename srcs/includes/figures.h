/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:09:56 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:25:03 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
#define FIGURES_H
#include "colors.h"
#include "vectors.h"
#include <stdbool.h>

typedef struct s_triangle
{
    t_vector a;
    t_vector b;
    t_vector c;
    t_vector normal;
    t_vector ab;
    t_vector ac;
    t_color  color;
    t_AABB   aabb;
} t_triangle;

typedef struct s_BVHNode
{
    union
    {
        struct
        {
            struct s_BVHNode* left;
            struct s_BVHNode* right;
        };
        struct
        {
            int count;
            t_triangle* batch;
        };
    };
    t_AABB  aabb;
    bool    is_leaf;
} t_BVHNode;

typedef struct s_BVH
{
    t_BVHNode* root;
    t_triangle*  triangles;
    int          triangle_count;
} t_BVH;

t_triangle new_triangle(t_vector frs_vector, t_vector sec_point, t_vector thd_point, t_color color);

#endif
