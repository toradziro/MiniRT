#ifndef COLORS_H
# define COLORS_H

typedef struct	t_color {
	float 	r;
	float 	g;
	float 	b;
}				s_color;

typedef struct	t_phong
{
	s_point		*intersec_point;
	s_vector	*light_dir;
	s_vector	*view_dir;
	s_vector	*halfway_dir;
	s_color		specular;
	float		spec;
}				s_phong;


#endif
