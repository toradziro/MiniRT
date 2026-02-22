#include "rt_thread.h"
#include <threads.h>
#include "../render/render.h"

int wrapper(void* thread_data)
{
    main_rt_loop(thread_data);
    return 0;
}

t_rt_thread create_thread(t_memory_arena* arena, void* thread_data)
{
    t_rt_thread thread;
    thrd_t* curr_thread = arena_push(arena, sizeof(thrd_t));
    thrd_create(curr_thread, wrapper, thread_data);
    thread.thread_data = curr_thread;
    return thread;
}

void thread_exit()
{
    thrd_exit(0);
}

void thread_join(t_rt_thread thread)
{
    thrd_t* curr_thread = thread.thread_data;
    thrd_join(*curr_thread, NULL);
}
