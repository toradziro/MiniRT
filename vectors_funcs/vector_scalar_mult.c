#include "../includes/MiniRT.h"

float			vector_scalar_mult(s_vector *a, s_vector *b)
{
	float		res;

	res = a->v_x * b->v_x + a->v_y * b->v_y + a->v_z * b->v_z;
	return (res);
}

s_vector		vector_by_scalar(s_vector *a, float num)
{
	s_vector	res;

	res.v_x = a->v_x * num;
	res.v_y = a->v_y * num;
	res.v_z = a->v_z * num;
	return (res);
}
