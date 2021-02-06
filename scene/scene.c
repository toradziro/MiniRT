#include "../includes/MiniRT.h"

s_scene		*new_scene(s_camera *cam, s_sphere *sphere)
{
	s_scene	*res;

	if (!(res = (s_scene*)malloc(sizeof(s_scene))))
		killed_by_error(MALLOC_ERROR);
	res->cams = cam;
	res->sphere = sphere;
	res->width = 0;
	res->height = 0;
	return (res);
}
