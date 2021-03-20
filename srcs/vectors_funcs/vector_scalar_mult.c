#include "../includes/MiniRT.h"

float			vector_scalar_mult(t_vector a, t_vector b)
{
	float		res;

	res = 0;
	res = a.v_x * b.v_x + a.v_y * b.v_y + a.v_z * b.v_z;
	return (res);
}

t_vector		vector_by_scalar(t_vector a, float num)
{
	t_vector	res;

	res = new_vector(0, 0, 0);
	res.v_x = a.v_x * num;
	res.v_y = a.v_y * num;
	res.v_z = a.v_z * num;
	return (res);
}
