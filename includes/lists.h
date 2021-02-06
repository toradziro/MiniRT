#ifndef FIGURES_H
# define FIGURES_H

typedef struct		t_figures {
		void 		*content;
		char 		specif;
		void 		*next;
}					s_figures;

typedef struct 		t_cameras {
		s_point		*coordinates;
		s_vector	*direction;
		double		field_of_v;
		void 		*next;
}					s_cameras;

typedef struct		t_lights {
		s_point		*coordinates;
		double		intensity;
		s_color		color;
		void		*next;
}					s_lights;

#endif
