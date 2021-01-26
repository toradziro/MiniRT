#ifndef SCENE_H
# define SCENE_H
# include "MiniRT.h"

typedef struct		t_scene {
		s_camera	*cams;
		s_sphere	*sphere;
		double		width;
		double		hieght;
}					s_scene;

s_scene		*new_scene(s_camera *cam, s_sphere *sphere);

#endif
