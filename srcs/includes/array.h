/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:09:28 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:15:21 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
#define ARRAY_H
#include "../arena/arena.h"
#include "../includes/my_types.h"
#include "figures.h"
#include "lists.h"

typedef union u_figure
{
    t_triangle triangle;
    t_cylinder cylender;
    t_square   square;
    t_plane    plane;
    t_sphere   sphere;
} u_figure;

typedef enum figure_type
{
    Triangle = 0,
    Cylender,
    Square,
    Plane,
    Sphere
} figure_type;

typedef struct s_figure_holder
{
    u_figure    _figure;
    figure_type type;
} __attribute__((aligned(16))) t_figure_holder;

typedef struct s_vec_fig
{
    t_figure_holder* figure_holder;
    int              length;
} t_vec_fig;

t_vec_fig* add_elem_vec(t_vec_fig* vec, t_figure_holder next);
t_vec_fig* new_vec_fig(u32 size, t_memory_arena* arena);

#endif
