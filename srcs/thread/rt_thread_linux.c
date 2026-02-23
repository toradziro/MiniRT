#include "rt_thread.h"
#include <pthread.h>
#include "../render/render.h"
#include <stdio.h>

void* wrapper(void* thread_data)
{
    main_rt_loop(thread_data);
    return NULL;
}

t_rt_thread create_thread(t_memory_arena* arena, void* thread_data)
{
    t_rt_thread thread;
    pthread_t*  curr_thread = arena_push(arena, sizeof(pthread_t));
    if (pthread_create(curr_thread, NULL, wrapper, thread_data))
    {
        printf("pthread_create(curr_thread, NULL, wrapper, thread_data\n");
        exit(1);
    }
    thread.thread_data = curr_thread;
    return thread;
}

void thread_exit() { pthread_exit(NULL); }

void thread_join(t_rt_thread thread)
{
    pthread_t* curr_thread = thread.thread_data;
    pthread_join(*curr_thread, NULL);
}
