#include "../includes/MiniRT.h"

t_vector		cross_prod(t_vector b, t_vector a)
{
	t_vector	res;

	res = new_vector(0, 0, 0);
	res.v_x = a.v_y * b.v_z - a.v_z * b.v_y;
	res.v_y = a.v_z * b.v_x - a.v_x * b.v_z;
	res.v_z = a.v_x * b.v_y - a.v_y * b.v_x;
	return (res);
}
