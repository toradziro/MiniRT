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
#include "../includes/figures.h"

typedef struct s_vec_fig
{
    t_triangle* triangles;
    int         length;
} t_vec_fig;

t_vec_fig* add_elem_vec(t_vec_fig* vec, t_triangle next);
t_vec_fig* new_vec_fig(u32 size, t_memory_arena* arena);

#endif
