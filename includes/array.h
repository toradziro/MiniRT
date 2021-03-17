#ifndef ARRAY_H
# define ARRAY_H
# include "lists.h"

typedef struct		t_vec_fig
{
	s_figures		*node;
	int				capacity;
	int				length;
}					s_vec_fig;

s_vec_fig		realloc_vec(s_vec_fig old);
s_vec_fig		add_elem_vec(s_vec_fig vec, s_figures *next);
s_vec_fig		new_vec_fig(void);
void			free_fig_test(s_vec_fig v);

#endif
