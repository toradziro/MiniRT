#include "vectors.h"

s_normal		vector_normalise(s_vector v, double len)
{
	s_normal	n;

	n.n_x = v.v_x / len;
	n.n_y = v.v_y / len;
	n.n_z = v.v_z / len;
	return (n);
}
