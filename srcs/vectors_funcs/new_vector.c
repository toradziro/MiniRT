#include "../includes/MiniRT.h"

t_vector		new_vector(double x, double y, double z)
{
	t_vector	new;

	new.v_x = x;
	new.v_y = y;
	new.v_z = z;
	return (new);
}
