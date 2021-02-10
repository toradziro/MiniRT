#ifndef SPHERE_H
# define SPHERE_H
# include "vectors.h"
#include "colors.h"

typedef struct		t_sphere {
		double		radius;
		s_point		*coordinates;
		s_color 	color;
}					s_sphere;

typedef struct		t_plane {
		s_vector	*coordinates;
		s_vector	*normal;
		s_color		color;
}					s_plane;

typedef struct		t_square {
		s_point		*center;
		s_vector	*normal;
		double		side;
		s_color		color;
}					s_square;

typedef struct		t_cylinder {
		s_point		*coordinates;
		s_vector	*normal;
		double		diameter;
		double		height;
		s_color		*color;
}					s_cylinder;

typedef struct		t_triangle {
		s_point		*frs_point;
		s_point		*sec_point;
		s_point		*thd_point;
		s_color		*color;
}					s_triangle;

s_triangle		*new_triangle(s_point *frs_point, s_point *sec_point, s_point *thd_point, s_color *color);
s_cylinder		*new_cylinder(s_point *coordinates, s_vector *normal, double diameter, double height, s_color *color);
s_square		*new_square(s_point *center, s_vector *normal, double side, s_color color);
s_plane			*new_plane(s_vector *coordinates, s_vector *normal, s_color color);
s_sphere		*new_sphere(double radius, s_point *coordinates, s_color color);

#endif
