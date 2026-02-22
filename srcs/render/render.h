/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:10:45 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:34:54 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
#define THREADS_H

#include "../ray_trace/ray_trace.h"
#include "../thread/rt_thread.h"

#ifndef THREADS_MAX
#define THREADS_MAX 4
#endif

typedef struct s_thread_data
{
    t_scene*      scene;
    int           curr_y;
    volatile bool is_task_assigned;
    volatile bool is_running;
} t_thread_data;

typedef struct s_thread_pool
{
    t_rt_thread        m_thread[THREADS_MAX];
    t_thread_data       m_thread_data[THREADS_MAX];
} t_thread_pool;

typedef struct s_thread
{
    int     id;
    t_scene scene;
} t_thread;

typedef struct s_ray_trace
{
    t_scene* scene;
    t_ray    ray;
    t_color  color;
    int      x_pixel;
    int      y_pixel;
} t_ray_trace;

void  main_rt_loop(void* thread_data);
void destroy_render(t_thread_pool* thread_pool);
void render(t_thread_pool* thread_pool, int y);
void start_render_threads(t_thread_pool* thread_pool, t_scene* scene, t_memory_arena* arena);

#endif
