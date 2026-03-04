/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:55 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 19:15:12 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
#define VECTORS_H

#include "math.h"
#include "rt_math.h"
#include "../lists_funcs/lists.h"

typedef struct s_cam_to_w
{
    float matrix[4][4];
} t_cam_to_w;

t_cam_to_w matrix_place(t_cameras* camera);
t_vector   matrix_mult(t_vector vec, t_cam_to_w m);

float vec_matrix_mult_first_row(t_vector vec, t_cam_to_w c);
float vec_matrix_mult_second_row(t_vector vec, t_cam_to_w c);

#endif
