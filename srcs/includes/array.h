#ifndef ARRAY_H
# define ARRAY_H
# include "lists.h"

typedef struct		s_vec_fig
{
	t_figures		*node;
	int				capacity;
	int				length;
}					t_vec_fig;

t_vec_fig		*realloc_vec(t_vec_fig *old);
t_vec_fig		*add_elem_vec(t_vec_fig *vec, t_figures next);
t_vec_fig		*new_vec_fig(void);
void			free_fig_test(t_vec_fig *v);

#endif
