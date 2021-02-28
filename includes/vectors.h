#ifndef VECTORS_H
# define VECTORS_H
# include "math.h"

typedef struct		t_vector {
		float		v_x;
		float		v_y;
		float		v_z;
}					s_vector;

typedef struct		t_point {
		float		p_x;
		float		p_y;
		float		p_z;
}					s_point;

typedef struct		t_ray {
		s_vector	*dir;
		s_point		*orig;
}					s_ray;

typedef struct		t_cam_to_w {
		float		matrix[4][4];
}					s_cam_to_w;

/**
 ** Subs (vec1 - vec2);
 ** add (vec1 + vec2);
 ** vec_scal_mult = (vector * vector) = dot product
 ** vector_cross = (vec * vec) = cross product
 ** vector_by_scalar = mult vector by const
 ** new_vector = create new vector
**/

s_point			*new_point(float x, float y, float z);
float			vector_scalar_mult(s_vector *a, s_vector *b);
float			vector_length(s_vector *v);
s_vector		*vector_normalise(s_vector *v, float len);
s_vector		*cross_prod(s_vector *a, s_vector *b);
s_vector		*add_vectors(s_vector *a, s_vector *b);
s_vector		*subs_vectors(s_vector *a, s_vector *b);
s_vector		*vector_by_scalar(s_vector *a, float num);
s_vector		*new_vector(float x, float y, float z);
s_vector		*vector_from_points(s_point *p1, s_point *p2);

s_cam_to_w		matrix_place(s_vector *coor, s_vector *dir);
s_vector		*matrix_mult(s_vector *vec, s_cam_to_w m);

#endif
