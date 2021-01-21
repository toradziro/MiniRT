#include "vectors.h"

s_vector		vector_normalise(s_vector v, double len)
{
	s_vector	n;

	n.v_x = v.v_x / len;
	n.v_y = v.v_y / len;
	n.v_z = v.v_z / len;
	return (n);
}
