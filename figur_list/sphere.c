#include "../includes/MiniRT.h"

s_sphere		*new_sphere(s_point *coordinates, double radius)
{
	s_sphere	*res;

	if (!(res = (s_sphere*)malloc(sizeof(s_sphere))))
		killed_by_error(-1);
	res->radius = radius;
	res->coordinates = coordinates;
	return (res);
}
