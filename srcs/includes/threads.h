#ifndef THREADS_H
# define THREADS_H
# include "MiniRT.h"

typedef struct		s_thread{
	int				id;
	t_scene			scene;
}					t_thread;

void			*ray_trace_thread(void *thread);
void			threads(t_scene *scene);

#endif
