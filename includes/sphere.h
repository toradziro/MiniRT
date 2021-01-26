#ifndef SPHERE_H
# define SPHERE_H
# include "vectors.h"

typedef struct	t_sphere {
		double	radius;
		s_point	*coordinates;
}				s_sphere;

s_sphere		*new_sphere(s_point *coordinates, double radius);

#endif
