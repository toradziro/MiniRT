#include "../includes/MiniRT.h"

t_vector		new_vector(float x, float y, float z)
{
	t_vector	new;

	new.v_x = x;
	new.v_y = y;
	new.v_z = z;
	return (new);
}
