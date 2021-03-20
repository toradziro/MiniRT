#include "../includes/MiniRT.h"

t_vector		add_vectors(t_vector a, t_vector b)
{
	t_vector	res;

	res = new_vector(0, 0, 0);
	res.v_x = a.v_x + b.v_x;
	res.v_y = a.v_y + b.v_y;
	res.v_z = a.v_z + b.v_z;
	return (res);
}

t_vector		subs_vectors(t_vector a, t_vector b)
{
	t_vector	res;

	res = new_vector(0, 0, 0);
	res.v_x = a.v_x - b.v_x;
	res.v_y = a.v_y - b.v_y;
	res.v_z = a.v_z - b.v_z;
	return (res);
}
