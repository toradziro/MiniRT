#ifndef FIGURES_H
# define FIGURES_H

typedef struct		s_figures{
	void			*content;
	char			specif;
}					t_figures;

typedef struct		s_cameras{
	t_vector		coordinates;
	t_vector		direction;
	void			*next;
	float			field_of_v;
}					t_cameras;

typedef struct		s_lights {
	t_vector		coordinates;
	t_vector		light_dir;
	void			*next;
	t_color			color;
	float			intensity;
}					t_lights;

typedef struct	s_ab_light {
	t_color		color;
	float		intensity;
}				t_ab_light;

t_figures		*new_figur_list(void *content, char spec);
t_cameras		*new_camera_node(t_vector coordinates, t_vector dir, float fov);
void			push_back_cam(t_cameras *list, t_cameras *new);
t_lights		*new_light_node(t_vector coordinates,
				float intensity, t_color color);
void			push_back_light(t_lights *list, t_vector coordinates,
				float intensity, t_color color);

#endif
