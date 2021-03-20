#include "../includes/MiniRT.h"

t_vec_fig		*new_vec_fig(void)
{
	t_vec_fig	*new;

	if (!(new = (t_vec_fig*)malloc(sizeof(t_vec_fig))))
		killed_by_error(MALLOC_ERROR);
	if (!(new->node = (t_figures*)malloc(sizeof(t_figures) * 2)))
		killed_by_error(MALLOC_ERROR);
	new->capacity = 2;
	new->length = 0;
	return (new);
}

t_vec_fig		*add_elem_vec(t_vec_fig *vec, t_figures next)
{
	t_vec_fig	*new;

	if (vec->length == vec->capacity)
	{
		new = realloc_vec(vec);
		new->node[new->length] = next;
		++new->length;
		return (new);
	}
	vec->node[vec->length] = next;
	++vec->length;
	return (vec);
}

t_vec_fig		*realloc_vec(t_vec_fig *old)
{
	t_vec_fig	*new;

	if (!(new = (t_vec_fig*)malloc(sizeof(t_vec_fig))))
		killed_by_error(MALLOC_ERROR);
	if (!(new->node =
	(t_figures*)malloc(sizeof(t_figures) * (old->capacity * 2))))
		killed_by_error(MALLOC_ERROR);
	new->capacity = (int)old->capacity * 2;
	memset(new->node, 0, sizeof(t_figures) * new->capacity);
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
