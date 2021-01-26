#include "../includes/MiniRT.h"

s_vector		*new_vector(double x, double y, double z)
{
	s_vector	*new;

	new = NULL;
	if(!(new = (s_vector*)malloc(sizeof(s_vector))))
		killed_by_error(-1);
	new->v_x = x;
	new->v_y = y;
	new->v_z = z;
	return (new);
}
