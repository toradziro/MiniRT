#ifndef VECTORS_H
# define VECTORS_H
# include "math.h"

typedef struct		t_vector {
		float		v_x;
		float		v_y;
		float		v_z;
}					s_vector;

typedef struct		t_ray {
		s_vector	dir;
		s_vector	orig;
}					s_ray;

typedef struct		t_cam_to_w {
		float		matrix[4][4];
}					s_cam_to_w;

float			vector_scalar_mult(s_vector a, s_vector b);
float			vector_length(s_vector v);
s_vector		vector_normalise(s_vector *v);
s_vector		cross_prod(s_vector a, s_vector b);
s_vector		add_vectors(s_vector a, s_vector b);
s_vector		subs_vectors(s_vector a, s_vector b);
s_vector		vector_by_scalar(s_vector *a, float num);
s_vector		new_vector(float x, float y, float z);

s_cam_to_w		matrix_place(s_vector coor, s_vector dir);
s_vector		matrix_mult(s_vector vec, s_cam_to_w m);

float			vec_matrix_mult_first_row(s_vector vec, s_cam_to_w c);
float			vec_matrix_mult_second_row(s_vector vec, s_cam_to_w c);

#endif
