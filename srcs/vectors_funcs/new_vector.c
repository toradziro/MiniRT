/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:15 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:23:50 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MiniRT.h"

t_vector new_vector(float x, float y, float z)
{
    t_vector new;

    new.v_x = x;
    new.v_y = y;
    new.v_z = z;
    return (new);
}

t_vector_vectorized to_vectorized(t_vector vec)
{
    t_vector_vectorized new;

    new.v_x = vec.v_x;
    new.v_y = vec.v_y;
    new.v_z = vec.v_z;
    new.v_w = 0.0f;
    return (new);
}
