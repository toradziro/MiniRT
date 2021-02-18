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

s_vector		*vector_from_points(s_point *p1, s_point *p2)
{
	s_vector	*res;

	res = new_vector(0, 0, 0);
	res->v_x = p2->p_x - p1->p_x;
	res->v_y = p2->p_y - p1->p_y;
	res->v_z = p2->p_z - p1->p_z;
	return (res);
}