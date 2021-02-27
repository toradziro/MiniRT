#ifndef THREADS_H
# define THREADS_H
# include "MiniRT.h"

typedef struct t_thread {
		int			id;
		s_scene		*scene;
}				s_thread;

void			*ray_trace_thread(void* thread);
void			threads(s_scene *scene);

#endif
