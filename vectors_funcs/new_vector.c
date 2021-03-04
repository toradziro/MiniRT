#include "../includes/MiniRT.h"

s_vector		new_vector(float x, float y, float z)
{
	s_vector	new;

	new.v_x = x;
	new.v_y = y;
	new.v_z = z;
	return (new);
}

s_point			new_point(float x, float y, float z)
{
	s_point		new;

	new.p_x = x;
	new.p_y = y;
	new.p_z = z;
	return(new);
}
