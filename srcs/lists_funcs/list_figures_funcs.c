
#include "../includes/MiniRT.h"

t_figures		*new_figur_list(void *content, char spec)
{
	t_figures	*new;

	if (!(new = (t_figures*)malloc(sizeof(t_figures))))
		killed_by_error(MALLOC_ERROR);
	new->content = content;
	new->specif = spec;
	return (new);
}
