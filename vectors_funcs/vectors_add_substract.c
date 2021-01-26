#include "../includes/MiniRT.h"

s_vector		*add_vectors(s_vector *a, s_vector *b)
{
	s_vector	*res;

	res = new_vector(0, 0, 0);
	res->v_x = a->v_x + b->v_x;
	res->v_y = a->v_y + b->v_y;
	res->v_z = a->v_z + b->v_z;
	return (res);
}

s_vector		*subs_vectors(s_vector *a, s_vector *b)
{
	s_vector	*res;

	res = new_vector(0, 0, 0);
	res->v_x = a->v_x - b->v_x;
	res->v_y = a->v_y - b->v_y;
	res->v_z = a->v_z - b->v_z;
	return (res);
}
