#include "../includes/MiniRT.h"

s_vector		new_vector(float x, float y, float z)
{
	s_vector	new;

	new.v_x = x;
	new.v_y = y;
	new.v_z = z;
	return (new);
}
