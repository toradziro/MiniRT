#include "../includes/MiniRT.h"

s_figures		*new_figur_list(void *content, char spec)
{
	s_figures	*new;

	if (!(new = (s_figures*)malloc(sizeof(s_figures))))
		killed_by_error(MALLOC_ERROR);
	new->content = (s_sphere*)content;
	new->specif = spec;
	new->next = NULL;
	return (new);
}

void		push_back_figur(s_figures *start, void *content, char spec)
{
	s_figures	*new;

	new = new_figur_list(content, spec);
	while (start->next != NULL)
		start = start->next;
	start->next = new;
}
