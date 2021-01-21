#ifndef VECTORS_H
# define VECTORS_H
# include <stdio.h> //DONT FORGET TO DELITE THIS SHIT
# include <stdlib.h>
# include <math.h>

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

typedef struct	t_normal {
				double n_x;
				double n_y;
				double n_z;
}				s_normal;

double			vector_scalar_mult(s_vector a, s_vector b);
double			vector_length(s_vector v);
s_normal		vector_normalise(s_vector v, double len);
s_vector		cross_prod(s_vector a, s_vector b);
s_vector		add_vectors(s_vector a, s_vector b);
s_vector		subs_vectors(s_vector a, s_vector b);

#endif
