#include "../includes/MiniRT.h"

s_camera		*new_camera(s_vector *dir, s_point *cor, double fov)
{
	s_camera	*res;

	if (!(res = (s_camera*)malloc(sizeof(s_camera))))
		killed_by_error(MALLOC_ERROR);
	res->direction = dir;
	res->coordinates = cor;
	res->field_of_v = fov;
	return (res);
}
