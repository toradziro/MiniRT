#ifndef SCENE_H
# define SCENE_H
# include "MiniRT.h"

typedef struct		t_scene {
		//s_camera	*cams;
		//list_of_cams
		s_sphere	*sphere;
		//list_of_figures
		//list_of_lights
		double		width; //screen
		double		height; //screen
}					s_scene;

//s_scene		*new_scene(s_camera *cam, s_sphere *sphere);

#endif
