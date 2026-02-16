/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:25:08 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:25:09 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_vec_fig* new_vec_fig(u32 size, t_memory_arena* arena)
{
    t_vec_fig* new     = (t_vec_fig*)arena_push_aligned(arena, sizeof(t_vec_fig), sizeof(t_vector));
    new->figure_holder = arena_push_aligned(arena, sizeof(t_figure_holder) * size, sizeof(t_vector));
    new->length        = 0;

    return (new);
}

t_vec_fig* add_elem_vec(t_vec_fig* vec, t_figure_holder next)
{
    vec->figure_holder[vec->length] = next;
    ++vec->length;
    return (vec);
}
