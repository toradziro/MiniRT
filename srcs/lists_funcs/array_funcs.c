#include "../includes/MiniRT.h"

s_vec_fig		*new_vec_fig(void)
{
	s_vec_fig	*new;

	if (!(new = (s_vec_fig*)malloc(sizeof(s_vec_fig))))
		killed_by_error(MALLOC_ERROR);
	if (!(new->node = (s_figures*)malloc(sizeof(s_figures) * 2)))
		killed_by_error(MALLOC_ERROR);
	new->capacity = 2;
	new->length = 0;
	return (new);
}

s_vec_fig		*add_elem_vec(s_vec_fig *vec, s_figures *next)
{
	s_vec_fig	*new;

	if (vec->length + 1 == vec->capacity)
	{
		new = realloc_vec(vec);
		new->node[vec->length] = *next;
		++new->length;
		return (new);
	}
	vec->node[vec->length] = *next;
	++vec->length;
	return (vec);
}

s_vec_fig		*realloc_vec(s_vec_fig *old)
{
	s_vec_fig	*new;

	if (!(new = (s_vec_fig*)malloc(sizeof(s_vec_fig))))
		killed_by_error(MALLOC_ERROR);
	if (!(new->node = (s_figures*)malloc(sizeof(s_figures) * (old->capacity * 2))))
		killed_by_error(MALLOC_ERROR);
	new->capacity = (int)old->capacity * 2;
	memset(new->node, 0, sizeof(s_figures) * new->capacity);
	new->length = 0;
	while (new->length < old->length)
	{
		new->node[new->length] = old->node[new->length];
		++new->length;
	}
	free(old->node);
	free(old);
	return (new);
}
