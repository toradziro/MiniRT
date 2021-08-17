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

#include "../includes/MiniRT.h"

t_cam_to_w			matrix_place(t_vector coor, t_vector dir)
{
	t_cam_to_w		res;
	t_vector		tmp;

	tmp = new_vector(0, 1, 0);
	tmp = cross_prod(tmp, dir);
	tmp = vector_normalise(tmp);
	res.matrix[0][0] = tmp.v_x;
	res.matrix[0][1] = tmp.v_y;
	res.matrix[0][2] = tmp.v_z;
	tmp = cross_prod(dir, tmp);
	tmp = vector_normalise(tmp);
	res.matrix[1][0] = tmp.v_x;
	res.matrix[1][1] = tmp.v_y;
	res.matrix[1][2] = tmp.v_z;
	res.matrix[2][0] = dir.v_x;
	res.matrix[2][1] = dir.v_y;
	res.matrix[2][2] = dir.v_z;
	res.matrix[3][0] = coor.v_x;
	res.matrix[3][1] = coor.v_y;
	res.matrix[3][2] = coor.v_z;
	return (res);
}

t_vector			matrix_mult(t_vector vec, t_cam_to_w m)
{
	t_vector		v;

	v = new_vector(0, 0, 0);
	v.v_x = vec.v_x * m.matrix[0][0] + vec.v_y * m.matrix[1][0] +
			vec.v_z * m.matrix[2][0] + m.matrix[3][0];
	v.v_y = vec.v_x * m.matrix[0][1] + vec.v_y * m.matrix[1][1] +
			vec.v_z * m.matrix[2][1] + m.matrix[3][1];
	v.v_z = vec.v_x * m.matrix[0][2] + vec.v_y * m.matrix[1][2] +
			vec.v_z * m.matrix[2][2] + m.matrix[3][2];
	return (vector_normalise(v));
}

float				vec_matrix_mult_first_row(t_vector vec, t_cam_to_w c)
{
	t_vector		tmp;

	tmp = new_vector(0, 0, 0);
	tmp = new_vector(c.matrix[0][0], c.matrix[0][1], c.matrix[0][2]);
	return (vector_scalar_mult(vec, tmp));
}

float				vec_matrix_mult_second_row(t_vector vec, t_cam_to_w c)
{
	t_vector		tmp;

	tmp = new_vector(0, 0, 0);
	tmp = new_vector(c.matrix[1][0], c.matrix[1][1], c.matrix[1][2]);
	return (vector_scalar_mult(vec, tmp));
}
