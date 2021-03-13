
#include "../includes/MiniRT.h"

s_figures		*new_figur_list(void *content, char spec)
{
	s_figures	*new;

	if (!(new = (s_figures*)malloc(sizeof(s_figures))))
		killed_by_error(MALLOC_ERROR);
	new->specif = S_NUL;
	new->content = content;
	new->specif = spec;
	return (new);
}
