#pragma once

#include "../arena/arena.h"

typedef struct s_rt_thread
{
    void* thread_data;
} t_rt_thread;

t_rt_thread create_thread(t_memory_arena* arena, void* thread_data);
void        thread_exit();
void        thread_join(t_rt_thread thread);
