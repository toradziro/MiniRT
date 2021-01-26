#include "../includes/MiniRT.h"

double		vector_scalar_mult(s_vector *a, s_vector *b)
{
	double	res;

	res = a->v_x * b->v_x + a->v_y * b->v_y + a->v_z * b->v_z;
	return (res);
}

s_vector		*vector_by_scalar(s_vector *a, double num)
{
	s_vector	*res;

	res = new_vector(0, 0, 0);
	res->v_x = a->v_x * num;
	res->v_y = a->v_y * num;
	res->v_z = a->v_z * num;
	return (res);
}
