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

#include "render.h"
#include "../includes/MiniRT.h"
#include "../includes/scene.h"

typedef struct s_stride_coeff
{
    float x;
    float y;
} t_stride_coeff;

void start_render_threads(t_thread_pool* thread_pool, t_scene* scene, t_memory_arena* arena)
{
    for (int i = 0; i < THREADS_MAX; ++i)
    {
        thread_pool->m_thread_data[i].is_running       = true;
        thread_pool->m_thread_data[i].is_task_assigned = false;
        thread_pool->m_thread_data[i].scene            = scene;
        thread_pool->m_thread[i]                       = create_thread(arena, &thread_pool->m_thread_data[i]);
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
        thread_join(thread_pool->m_thread[i]);
    }
}

void set_color(void* pixels, t_color* color, i32 x, i32 y, i32 width)
{
    void* color_ptr    = (((u32*)pixels) + (width * y) + x);
    (*(u32*)color_ptr) = (int)color->r << 16 | (int)color->g << 8 | (int)color->b;
}

//-- We need to move a ray inside the pixel to gain anti-aliasing
t_stride_coeff calculate_stride(t_accum_data* accum)
{
    t_stride_coeff res;
    if (!(accum->count % 4))
    {
        res.x = 0.25f;
        res.y = 0.25f;
    }
    else if (!(accum->count % 3))
    {
        res.x = 0.75f;
        res.y = 0.25f;
    }
    else if (!(accum->count % 2))
    {
        res.x = 0.25f;
        res.y = 0.75f;
    }
    else
    {
        res.x = 0.75f;
        res.y = 0.75f;
    }
    return res;
}

void main_rt_loop(void* thread_data)
{
    t_thread_data* curr_thread_data = (t_thread_data*)thread_data;
    while (curr_thread_data->is_running)
    {
        if (!curr_thread_data->is_task_assigned)
        {
            continue;
        }
        t_ray_trace trace;
        trace.scene    = curr_thread_data->scene;
        trace.y_pixel  = curr_thread_data->curr_y;
        trace.x_pixel  = 0;
        trace.ray.orig = trace.scene->cams->coordinates;

        while (trace.x_pixel < trace.scene->width)
        {
            //-- Accumulative anti-aliasing
            if (trace.scene->roughness_and_multisample)
            {
                t_accum_data*  accum  = trace.scene->pixels_avg + (trace.y_pixel * trace.scene->width) + trace.x_pixel;
                t_stride_coeff coeffs = calculate_stride(accum);

                trace.ray.dir.v_x = (trace.x_pixel - (trace.scene->width * 0.5)) + coeffs.x;
                trace.ray.dir.v_y = (-trace.y_pixel + (trace.scene->height * 0.5)) + coeffs.y;
            }
            else
            {
                trace.ray.dir.v_x = trace.x_pixel - (trace.scene->width * 0.5);
                trace.ray.dir.v_y = -trace.y_pixel + (trace.scene->height * 0.5);
            }
            trace.ray.dir.v_z = trace.scene->projection_coeff;
            trace.ray.dir     = matrix_mult(trace.ray.dir, trace.scene->mtrx);
            trace.color       = ray_trace(trace.scene, trace.ray, trace.x_pixel, trace.y_pixel);
            set_color(trace.scene->pixels, &trace.color, trace.x_pixel, trace.y_pixel, trace.scene->width);

            trace.x_pixel++;
        }
        curr_thread_data->is_task_assigned = false;
    }
    thread_exit();
}
