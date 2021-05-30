#ifndef VECTORS_H
# define VECTORS_H
# include "math.h"

typedef struct		s_vector {
	double			v_x;
	double			v_y;
	double			v_z;
}					t_vector;

typedef struct		s_ray {
	t_vector		dir;
	t_vector		orig;
}					t_ray;

typedef struct		s_cam_to_w {
	double			matrix[4][4];
}					t_cam_to_w;

double				vector_scalar_mult(t_vector a, t_vector b);
double				vector_length(t_vector v);
t_vector			vector_normalise(t_vector v);
t_vector			cross_prod(t_vector a, t_vector b);
t_vector			add_vectors(t_vector a, t_vector b);
t_vector			subs_vectors(t_vector a, t_vector b);
t_vector			vector_by_scalar(t_vector a, double num);
t_vector			new_vector(double x, double y, double z);

t_cam_to_w			matrix_place(t_vector coor, t_vector dir);
t_vector			matrix_mult(t_vector vec, t_cam_to_w m);

double				vec_matrix_mult_first_row(t_vector vec, t_cam_to_w c);
double				vec_matrix_mult_second_row(t_vector vec, t_cam_to_w c);

#endif
