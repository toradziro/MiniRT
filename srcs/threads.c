/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:46:41 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:32:06 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/threads.h"
#include "includes/MiniRT.h"
#include "includes/parser.h"

void start_render_threads(t_thread_pool* thread_pool, t_scene* scene)
{
    for (int i = 0; i < THREADS_MAX; ++i)
    {
        thread_pool->m_thread_data[i].is_running       = true;
        thread_pool->m_thread_data[i].is_task_assigned = false;
        thread_pool->m_thread_data[i].scene            = scene;

        if (pthread_create(&thread_pool->m_thread[i], NULL, main_rt_loop, &thread_pool->m_thread_data[i]))
        {
            killed_by_error(MALLOC_ERROR);
        }
    }
}

void render(t_thread_pool* thread_pool, int y)
{
    for (int i = 0; i < y;)
    {
        for (int j = 0; j < THREADS_MAX && i < y; ++j)
        {
            if (!thread_pool->m_thread_data[j].is_task_assigned)
            {
                thread_pool->m_thread_data[j].curr_y = i;

                thread_pool->m_thread_data[j].is_task_assigned = true;
                ++i;
            }
        }
    }
}

void destroy_render(t_thread_pool* thread_pool)
{
    for (int i = 0; i < THREADS_MAX; ++i)
    {
        thread_pool->m_thread_data[i].is_running = false;
    }
    for (int i = 0; i < THREADS_MAX; ++i)
    {
        pthread_join(thread_pool->m_thread[i], NULL);
    }
}

void* main_rt_loop(void* thread_data)
{
    t_thread_data* curr_thread_data = (t_thread_data*)thread_data;
    while (curr_thread_data->is_running)
    {
        if (!curr_thread_data->is_task_assigned)
        {
            // _mm_pause();
            continue;
        }
        t_ray_trace trace;
        trace.scene    = curr_thread_data->scene;
        trace.y_pixel  = curr_thread_data->curr_y;
        trace.x_pixel  = 0;
        trace.ray.orig = trace.scene->cams->coordinates;

        while (trace.x_pixel < trace.scene->width)
        {
            trace.coefs[1] = -trace.y_pixel + (trace.scene->height * 0.5);
            trace.coefs[0] = trace.x_pixel - (trace.scene->width * 0.5);
            trace.coefs[2] = trace.scene->projection_coeff;
            trace.ray.dir  = new_vector(trace.coefs[0], trace.coefs[1], trace.coefs[2]);
            trace.ray.dir  = matrix_mult(trace.ray.dir, trace.scene->mtrx);
            trace.color    = intersec(trace.scene, trace.ray);
            //-- TODO: Make a function
            void* color_ptr    = (((u32*)trace.scene->pixels) + (trace.scene->width * trace.y_pixel) + trace.x_pixel);
            (*(u32*)color_ptr) = (int)trace.color.r << 16 | (int)trace.color.g << 8 | (int)trace.color.b;
            trace.x_pixel++;
        }
        curr_thread_data->is_task_assigned = false;
    }
    pthread_exit(NULL);
}
