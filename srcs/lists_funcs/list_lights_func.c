/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lights_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:29:45 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:30:38 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

t_lights* new_light_node(t_vector coordinates, float intensity, t_color color, t_memory_arena* arena)
{
    t_lights* new = arena_push(arena, sizeof(t_lights));
    t_vector tmp;

    tmp              = new_vector(0, 0, 0);
    new->coordinates = coordinates;
    new->intensity   = intensity;
    new->color       = color;
    new->light_dir   = tmp;
    new->next        = NULL;
    return (new);
}

void push_back_light(t_lights* list, t_vector coordinates, float intensity, t_color color, t_memory_arena* arena)
{
    t_lights* tmp;

    tmp = new_light_node(coordinates, intensity, color, arena);
    while (list->next)
    {
        list = list->next;
    }
    list->next = tmp;
}
