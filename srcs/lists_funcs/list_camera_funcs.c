/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_camera_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:27:23 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:47:16 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_cameras* new_camera_node(t_vector coordinates, t_vector dir, float fov, t_memory_arena* arena)
{
    t_cameras* new = arena_push(arena, sizeof(t_cameras));

    new->coordinates = coordinates;
    new->direction   = dir;
    new->field_of_v  = fov;
    new->next        = NULL;
    return (new);
}

void push_back_cam(t_cameras* list, t_cameras* new)
{
    while (list->next)
    {
        list = list->next;
    }
    list->next = new;
}
