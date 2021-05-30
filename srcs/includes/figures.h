#ifndef FIGURES_H
# define FIGURES_H
# include "vectors.h"
# include "colors.h"

typedef struct		s_sphere{
	t_vector		coordinates;
	t_color			color;
	double			radius;
}					t_sphere;

typedef struct		s_plane{
	t_vector		coordinates;
	t_vector		normal;
	t_color			color;
}					t_plane;

typedef struct		s_square{
	t_vector		center;
	t_vector		normal;
	double			side;
	t_color			color;
}					t_square;

typedef struct		s_cylinder{
	t_vector		coordinates;
	t_vector		normal;
	double			diameter;
	double			height;
	t_vector		axis;
	t_color			color;
}					t_cylinder;

typedef struct		s_triangle{
	t_vector		a;
	t_vector		b;
	t_vector		c;
	t_vector		normal;
	t_vector		ab;
	t_vector		ac;
	t_color			color;
}					t_triangle;

t_triangle			*new_triangle(t_vector frs_vector, t_vector sec_point,
					t_vector thd_point, t_color color);
t_cylinder			*new_cylinder(t_vector coordinates, t_vector normal,
					double diameter, double height, t_color color);
t_square			*new_square(t_vector center, t_vector normal,
					double side, t_color color);
t_plane				*new_plane(t_vector coordinates,
					t_vector normal, t_color color);
t_sphere			*new_sphere(double radius, t_vector
					coordinates, t_color color);

#endif
