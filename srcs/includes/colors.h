#ifndef COLORS_H
# define COLORS_H

typedef struct	s_color {
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct	s_phong
{
	t_vector	intersec_point;
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	halfway_dir;
	t_color		specular;
	float		spec;
}				t_phong;
#endif
