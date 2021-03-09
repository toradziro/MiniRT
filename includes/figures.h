#ifndef SPHERE_H
# define SPHERE_H
# include "vectors.h"
#include "colors.h"

typedef struct		t_sphere {
		s_vector	coordinates;
		s_color 	color;
		float		radius;
}					s_sphere;

typedef struct		t_plane {
		s_vector	coordinates;
		s_vector	normal;
		s_color		color;
}					s_plane;

typedef struct		t_square {
		s_vector	center;
		s_vector	normal;
		float		side;
		s_color		color;
}					s_square;

typedef struct		t_cylinder {
		s_vector	coordinates;
		s_vector	normal;
		float		diameter;
		float		height;
		s_color		color;
}					s_cylinder;

typedef struct		t_triangle {
		s_vector	a;
		s_vector	b;
		s_vector	c;
		s_vector	normal;
		s_vector	ab;
		s_vector	ac;
		s_vector	bc;
		s_color		color;
}					s_triangle;

s_triangle		*new_triangle(s_vector frs_vector, s_vector sec_point, s_vector thd_point, s_color color);
s_cylinder		*new_cylinder(s_vector coordinates, s_vector normal, float diameter, float height, s_color color);
s_square		*new_square(s_vector center, s_vector normal, float side, s_color color);
s_plane			*new_plane(s_vector coordinates, s_vector normal, s_color color);
s_sphere		*new_sphere(float radius, s_vector coordinates, s_color color);

#endif
