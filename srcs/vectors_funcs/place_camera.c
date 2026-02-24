/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:37:26 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/20 23:59:52 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "matrix.h"
#include <math.h>

t_cam_to_w matrix_place(t_cameras* camera)
{
    t_cam_to_w res;
    t_vector   tmp;

    camera->direction.v_x = cos(camera->yaw) * cos(camera->pitch);
    camera->direction.v_y = sin(camera->pitch);
    camera->direction.v_z = sin(camera->yaw) * cos(camera->pitch);
    camera->direction = vector_normalize(&camera->direction);
    // camera->up =;

    tmp              = camera->up;
    tmp              = cross_prod(&tmp, &camera->direction);
    tmp              = vector_normalize(&tmp);
    res.matrix[0][0] = tmp.v_x;
    res.matrix[0][1] = tmp.v_y;
    res.matrix[0][2] = tmp.v_z;
    tmp              = cross_prod(&camera->direction, &tmp);
    tmp              = vector_normalize(&tmp);
    res.matrix[1][0] = tmp.v_x;
    res.matrix[1][1] = tmp.v_y;
    res.matrix[1][2] = tmp.v_z;
    res.matrix[2][0] = camera->direction.v_x;
    res.matrix[2][1] = camera->direction.v_y;
    res.matrix[2][2] = camera->direction.v_z;
    res.matrix[3][0] = camera->coordinates.v_x;
    res.matrix[3][1] = camera->coordinates.v_y;
    res.matrix[3][2] = camera->coordinates.v_z;
    return (res);
}

t_vector matrix_mult(t_vector vec, t_cam_to_w m)
{
    t_vector v;

    t_vector col0 = new_vector(m.matrix[0][0], m.matrix[1][0], m.matrix[2][0]);
    t_vector col1 = new_vector(m.matrix[0][1], m.matrix[1][1], m.matrix[2][1]);
    t_vector col2 = new_vector(m.matrix[0][2], m.matrix[1][2], m.matrix[2][2]);
    v.v_x         = vector_scalar_mult(&vec, &col0);
    v.v_y         = vector_scalar_mult(&vec, &col1);
    v.v_z         = vector_scalar_mult(&vec, &col2);
    return (vector_normalize(&v));
}

float vec_matrix_mult_first_row(t_vector vec, t_cam_to_w c)
{
    t_vector tmp;

    tmp = new_vector(c.matrix[0][0], c.matrix[0][1], c.matrix[0][2]);
    return (vector_scalar_mult(&vec, &tmp));
}

float vec_matrix_mult_second_row(t_vector vec, t_cam_to_w c)
{
    t_vector tmp;

    tmp = new_vector(c.matrix[1][0], c.matrix[1][1], c.matrix[1][2]);
    return (vector_scalar_mult(&vec, &tmp));
}
