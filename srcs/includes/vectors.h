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
# define VECTORS_H
# include "math.h"

typedef struct		s_vector {
	float			v_x;
	float			v_y;
	float			v_z;
}					t_vector;

typedef struct		s_ray {
	t_vector		dir;
	t_vector		orig;
}					t_ray;

typedef struct		s_cam_to_w {
	float			matrix[4][4];
}					t_cam_to_w;

float				vector_scalar_mult(t_vector a, t_vector b);
float				vector_length(t_vector v);
t_vector			vector_normalise(t_vector v);
t_vector			cross_prod(t_vector a, t_vector b);
t_vector			add_vectors(t_vector a, t_vector b);
t_vector			subs_vectors(t_vector a, t_vector b);
t_vector			vector_by_scalar(t_vector a, float num);
t_vector			new_vector(float x, float y, float z);

t_cam_to_w			matrix_place(t_vector coor, t_vector dir);
t_vector			matrix_mult(t_vector vec, t_cam_to_w m);

float				vec_matrix_mult_first_row(t_vector vec, t_cam_to_w c);
float				vec_matrix_mult_second_row(t_vector vec, t_cam_to_w c);

#endif
