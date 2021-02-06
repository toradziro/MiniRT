#ifndef SCENE_H
# define SCENE_H
# include "lists.h"

typedef struct		t_scene {
		s_cameras	*cams;
		s_figures	*figures;
		s_lights	*lights;
		int 		is_cam;
		int 		is_light;
		int 		is_size;
		int 		is_amb_l;
		int 		is_figur;
		double		width;
		double		height;
}					s_scene;

//s_scene		*new_scene(s_camera *cam, s_sphere *sphere);

#endif
