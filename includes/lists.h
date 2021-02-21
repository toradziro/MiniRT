#ifndef FIGURES_H
# define FIGURES_H

typedef struct		t_figures {
		void 		*content;
		void	 	*next;
		char 		specif;
}					s_figures;

typedef struct 		t_cameras {
		s_point		*coordinates;
		s_vector	*direction;
		void 		*next;
		double		field_of_v;
}					s_cameras;

typedef struct		t_lights {
		s_point		*coordinates;
		void		*next;
		s_color		color;
		double		intensity;
}					s_lights;

typedef struct	t_ab_light {
	s_color		color;
	double		intensity;
}				s_ab_light;

s_figures		*new_figur_list(void *content, char spec);
void			push_back_figur(s_figures *start, void *content, char spec);
s_cameras		*new_camera_node(s_point *coordinates, s_vector *dir, double fov);
void 			push_back_cam(s_cameras *list, s_point *coordinates, s_vector *dir, double fov);
s_lights		*new_light_node(s_point *coordinates, double intensity, s_color color);
void	 		push_back_light(s_lights *list , s_point *coordinates, double intensity, s_color color);

#endif
