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
#include "../vectors_funcs/rt_math.h"
#include <stdbool.h>
#include "../bvh/aabb.h"

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
    float    reflection_value;
    bool     reflective;
} t_triangle;

t_triangle new_triangle(t_vector frs_vector, t_vector sec_point, t_vector thd_point, t_color color);

#endif
