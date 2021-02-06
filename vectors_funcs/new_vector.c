#include "../includes/MiniRT.h"

s_vector		*new_vector(double x, double y, double z)
{
	s_vector	*new;

	if (!(new = (s_vector*)malloc(sizeof(s_vector))))
		killed_by_error(MALLOC_ERROR);
	new->v_x = x;
	new->v_y = y;
	new->v_z = z;
	return (new);
}

s_point			*new_point(double x, double y, double z)
{
	s_point		*new;

	if (!(new = (s_point*)malloc(sizeof(s_point))))
		killed_by_error(MALLOC_ERROR);
	new->p_x = x;
	new->p_y = y;
	new->p_z = z;
	return(new);
}
