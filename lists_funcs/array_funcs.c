#include "../includes/MiniRT.h"

/*
** add_elem
** realloc_array
** capacity, curr_length, void *content
*/

s_vec_fig		*new_vec_fig(void)
{
	s_vec_fig	*new;

	if (!(new = (s_vec_fig*)malloc(sizeof(s_vec_fig))))
		killed_by_error(MALLOC_ERROR);
	if (!(new->node = (s_figures*)malloc(sizeof(s_figures) * 10)))
		killed_by_error(MALLOC_ERROR);
	new->capacity = 10;
	new->length = 0;
	return (new);
}

s_vec_fig		*add_elem_vec(s_vec_fig *vec, s_figures *next)
{
	if (vec->length + 1 >= vec->capacity)
		vec = realloc_vec(vec, next);
	vec->node[vec->length] = *next;
	++vec->length;
	return (vec);
}

s_vec_fig		*realloc_vec(s_vec_fig *old, s_figures *next)
{
	s_vec_fig	*new;

	if (!(new = (s_vec_fig*)malloc(sizeof(s_vec_fig))))
		killed_by_error(MALLOC_ERROR);
	if (!(new->node = (s_figures*)malloc(sizeof(s_figures) * (old->capacity * 2))))
		killed_by_error(MALLOC_ERROR);
	new->capacity = old->capacity * 2;
	new->length = 0;
	while (new->length <= old->length)
	{
		new->node[new->length] = old->node[new->length];
		++new->length;
	}
	printf("%d\n", new->length);
	free(old->node);
	free(old);
	return (new);
}

void			free_fig(s_vec_fig *vec)
{
	s_figures	*tmp;

	tmp = NULL;
	while (vec->length >= 0)
	{
		tmp = &vec->node[vec->length - 1];
		free((void*)tmp);
		--vec->length;
	}
}
