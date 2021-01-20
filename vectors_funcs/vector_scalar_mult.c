#include "vectors.h"

double	vector_scalar_mult(s_vector a, s_vector b)
{
	double	res;

	res = a.v_x * b.v_x + a.v_y * b.v_y + a.v_z * b.v_z;
	return (res);
}
