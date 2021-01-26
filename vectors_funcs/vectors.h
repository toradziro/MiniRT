#ifndef VECTORS_H
# define VECTORS_H

typedef struct	t_vector {
				double v_x;
				double v_y;
				double v_z;
}				s_vector;

typedef struct	t_point {
				double p_x;
				double p_y;
				double p_z;
}				s_point;

typedef struct	t_ray {
				s_vector dir;
				s_point orig;
}				s_ray;

double			**matrix_multip(double **a, double **b);
double			vector_scalar_mult(s_vector a, s_vector b);
double			vector_length(s_vector v);
double			**matrix_decl(int num);
s_vector		vector_normalise(s_vector v, double len);
s_vector		cross_prod(s_vector a, s_vector b);
s_vector		add_vectors(s_vector a, s_vector b);
s_vector		subs_vectors(s_vector a, s_vector b);
s_vector		vector_by_scalar(s_vector a, double num);
s_vector		*new_vector(double x, double y, double z);

#endif
