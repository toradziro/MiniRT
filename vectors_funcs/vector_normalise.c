#include "../includes/MiniRT.h"

s_vector		vector_normalise(s_vector v)
{
	s_vector	n;
	float 		len;
	float 		len_coeff;

	len = sqrt(v.v_x * v.v_x + v.v_y * v.v_y + v.v_z * v.v_z);
	len_coeff = 1 / len;
	n.v_x = v.v_x * len_coeff;
	n.v_y = v.v_y * len_coeff;
	n.v_z = v.v_z * len_coeff;
	return (n);
}
