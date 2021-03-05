#ifndef FIGURES_H
# define FIGURES_H

typedef struct		t_figures {
		void 		*content;
		void		*next;
		char 		specif;
}					s_figures;

typedef struct 		t_cameras {
		s_vector		coordinates;
		s_vector	direction;
		void 		*next;
		float		field_of_v;
}					s_cameras;

typedef struct		t_lights {
		s_vector		coordinates;
		s_vector	light_dir;
		void		*next;
		s_color		color;
		float		intensity;
}					s_lights;

typedef struct	t_ab_light {
	s_color		color;
	float		intensity;
}				s_ab_light;

s_figures		*new_figur_list(void *content, char spec);
void			push_back_figur(s_figures *start, void *content, char spec);
s_cameras		*new_camera_node(s_vector coordinates, s_vector dir, float fov);
void 			push_back_cam(s_cameras *list, s_vector coordinates, s_vector dir, float fov);
s_lights		*new_light_node(s_vector coordinates, float intensity, s_color color);
void 			push_back_light(s_lights *list, s_vector coordinates, float intensity, s_color color);

#endif
