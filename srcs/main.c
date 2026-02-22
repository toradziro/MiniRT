/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehillman <ehillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:37:17 by ehillman          #+#    #+#             */
/*   Updated: 2021/03/21 00:06:18 by ehillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena/arena.h"
#include "includes/MiniRT.h"
#include "lists_funcs/array.h"
#include "includes/my_types.h"
#include "parser/parser.h"
#include "render/render.h"
#include "bvh/bvh.h"
#include "utilits/rt_time.h"
#include "unity_build.h"
#include "window/window.h"
#include <stdio.h>

#define M_PI (3.14159)

int main(int argc, char** argv)
{
    t_memory_arena global_arena = create_arena(GB(1));
    t_scene        scene;
    memset(&scene, 0, sizeof(scene));

    if (argc < 2 || argc > 4)
    {
        killed_by_error(INV_AM_OF_ARG);
    }
    check_valid_name(argv[1]);

    start_parse(&scene, argv[1], &global_arena);
    check_scene(&scene);
    assignAABB(scene.figures);
    scene.bvh = buildBVH(scene.figures->triangles, scene.figures->length, &global_arena);

    //-- Roughness will be set the same for all reflective primitives
    //-- Better to avoid passing values bigger then 0.1
    if (argc == 4 && !strcmp(argv[2], "--roughness_and_multisample"))
    {
        scene.roughness_and_multisample = true;
        scene.roughness_val             = d_atoi(argv[3]);
    }
    else if (argc == 3 && !strcmp(argv[2], "--save"))
    {
        scene.is_save = 1;
    }
    else if (argc != 2)
    {
        killed_by_error(UNKNWN_ARG);
    }

    scene.pixels     = arena_push(&global_arena, scene.width * scene.height * sizeof(i32));
    scene.pixels_avg = arena_push(&global_arena, scene.width * scene.height * sizeof(t_accum_data));
    memset(scene.pixels_avg, 0, scene.width * scene.height * sizeof(t_accum_data));

    t_window window = create_window("MiniRT", scene.width, scene.height, &global_arena);
    window.buffer   = scene.pixels;

    scene.is_running = true;
    t_thread_pool thread_pool;
    start_render_threads(&thread_pool, &scene, &global_arena);

    while (scene.is_running)
    {
        const u32 time_frame_start = time_ms();

        process_events(&window, &scene);

        scene.mtrx             = matrix_place(scene.cams->coordinates, scene.cams->direction);
        scene.projection_coeff = scene.width / (2 * tan(scene.cams->field_of_v * 0.5 * M_PI * 0.00555555555));
        render(&thread_pool, scene.height);

        present_buffer_in_window(&window);

        const u32 time_frame_end = time_ms();
        const u32 time_elapsed   = time_frame_end - time_frame_start;
        printf("MS: %u -- FPS: %u\n", time_elapsed, 1000 / time_elapsed);
    }

    destroy_render(&thread_pool);
    destroy_window(&window);
    destroy_arena(&global_arena);
    return (0);
}

int exit_rt(t_scene* scene)
{
    scene->is_running = false;
    return (0);
}

void check_scene(t_scene* scene)
{
    if (!scene->ab_light || !scene->cams || !scene->figures || !scene->lights ||
        (scene->width == 0 && scene->height == 0))
    {
        killed_by_error(NOT_ENOUGH);
    }
}
