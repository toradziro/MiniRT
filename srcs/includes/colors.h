#ifndef COLORS_H
# define COLORS_H

typedef struct	s_color {
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct	s_phong
{
	t_vector	intersec_point;
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	halfway_dir;
	t_color		specular;
	double		spec;
}				t_phong;
#endif
