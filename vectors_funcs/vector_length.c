#include "../includes/MiniRT.h"

double	vector_length(s_vector *v)
{
	return (sqrt(v->v_x * v->v_x + v->v_y * v->v_y + v->v_z * v->v_z));
}
