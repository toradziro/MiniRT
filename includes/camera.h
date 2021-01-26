#ifndef CAMERA_H
# define CAMERA_H
# include "vectors.h"

typedef struct		t_camera {
		s_point		*coordinates;
		s_vector	*direction;
		double		field_of_v;
}					s_camera;

s_camera		*new_camera(s_vector *dir, s_point *cor, double fov);

#endif
