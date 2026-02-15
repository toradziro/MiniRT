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

#define M_PI (3.14159)

void threads(t_scene* scene)
{
    t_thread  thread_id[THREADS_MAX];
    pthread_t thread[THREADS_MAX];

    scene->mtrx = matrix_place(scene->cams->coordinates, scene->cams->direction);
    threads_start(thread_id, thread, scene);
    if (scene->is_save)
    {
        save_to_bmp(scene);
        exit_rt(scene);
    }
}

void threads_start(t_thread* thread_id, pthread_t* thread, t_scene* scene)
{
    int i;

    i = 0;
    while (i < THREADS_MAX)
    {
        thread_id[i].id    = i;
        thread_id[i].scene = *scene;
        if (pthread_create(&thread[i], NULL, ray_trace_thread, &thread_id[i]))
        {
            killed_by_error(MALLOC_ERROR);
        }
        ++i;
    }
    i = 0;
    while (i < THREADS_MAX)
    {
        pthread_join(thread[i], NULL);
        ++i;
    }
}

void* ray_trace_thread(void* thread)
{
    t_ray_trace trace;

    trace.curr_thr = (t_thread*)thread;
    trace.scene    = &(trace.curr_thr->scene);
    trace.y_pixel  = trace.curr_thr->id * (trace.scene->height / THREADS_MAX);
    trace.y_end    = trace.y_pixel + (trace.scene->height / THREADS_MAX);
    trace.ray.orig = trace.scene->cams->coordinates;
    main_rt_loop(trace);
    pthread_exit(NULL);
}

void main_rt_loop(t_ray_trace trace)
{
    while (trace.y_pixel < trace.y_end)
    {
        trace.x_pixel = 0;
        while (trace.x_pixel < trace.scene->width)
        {
            trace.coefs[1] = -trace.y_pixel + (trace.scene->height * 0.5);
            trace.coefs[0] = trace.x_pixel - (trace.scene->width * 0.5);
            trace.coefs[2] = trace.scene->width / (2 * tan(trace.scene->cams->field_of_v * 0.5 * M_PI * 0.00555555555));
            trace.ray.dir  = new_vector(trace.coefs[0], trace.coefs[1], trace.coefs[2]);
            trace.ray.dir  = matrix_mult(trace.ray.dir, trace.scene->mtrx);
            trace.ray.dir  = vector_normalise(trace.ray.dir);
            trace.color    = intersec(trace.scene, trace.ray);
            trace.ret_color = (int)trace.color.r << 16 | (int)trace.color.g << 8 | (int)trace.color.b;
            //-- TODO: Make a function
            void* color_ptr    = (((u32*)trace.scene->pixels) + (trace.scene->width * trace.y_pixel) + trace.x_pixel);
            (*(u32*)color_ptr) = trace.ret_color;
            trace.x_pixel++;
        }
        trace.y_pixel++;
    }
}
