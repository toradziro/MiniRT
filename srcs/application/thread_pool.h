#pragma once

#include "../thread/rt_thread.h"
#include <stdbool.h>

#ifndef THREADS_MAX
#define THREADS_MAX 1
#endif

typedef struct s_thread_data
{
    void*         scene;
    i32           curr_y;
    volatile bool is_task_assigned;
    volatile bool is_running;
} t_thread_data;

typedef struct s_thread_pool
{
    t_rt_thread   m_thread[THREADS_MAX];
    t_thread_data m_thread_data[THREADS_MAX];
} t_thread_pool;
