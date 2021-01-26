#include "../MiniRT.h"

s_vector		*new_vector(double x, double y, double z)
{
	s_vector	*new;

	if(!(new = (s_vector*)malloc(sizeof(s_vector) * 1)))
		return (NULL);
	new->v_x = x;
	new->v_y = y;
	new->v_z = z;
	return (new);
}
