#include "../includes/MiniRT.h"

t_vector		vector_normalise(t_vector v)
{
	double		len;
	double		len_coeff;
	t_vector	n;

	n = new_vector(0, 0, 0);
	len = sqrt(v.v_x * v.v_x + v.v_y * v.v_y + v.v_z * v.v_z);
	len_coeff = 1 / len;
	n.v_x = v.v_x * len_coeff;
	n.v_y = v.v_y * len_coeff;
	n.v_z = v.v_z * len_coeff;
	return (n);
}
