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
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "bvh/bvh.h"
#include "unity_build.h"

#define M_PI (3.14159)

void handle_event(SDL_Event* event, t_scene* scene)
{
    switch (event->type)
    {
    case SDL_QUIT:
    {
        exit_rt(scene);
    }
    break;

    case SDL_WINDOWEVENT:
    {
        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
        {
        }
        break;
        }
    }
    break;
    case SDL_KEYDOWN:
    {
        press_key(event->key.keysym, scene);
    }
    break;
    }
}

u64 time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000 + (u64)ts.tv_nsec / 1000000;
}

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
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //-- TODO: Add new error
        killed_by_error(MALLOC_ERROR);
    }
    start_parse(&scene, argv[1], &global_arena);
    check_scene(&scene);
    assignAABB(scene.figures);
    scene.bvh = buildBVH(scene.figures->triangles, scene.figures->length, &global_arena);

    SDL_Window* sdl_window =
        SDL_CreateWindow("MiniRT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scene.width, scene.height,
                         /*SDL_WINDOW_RESIZABLE*/ 0);
    scene.window = sdl_window;

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
    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    //-- TODO: recreate on window resize
    SDL_Texture* backbuffer_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888,
                                                        SDL_TEXTUREACCESS_STREAMING, scene.width, scene.height);

    scene.is_running = true;
    //-- TODO: Cleanup
    t_thread_pool thread_pool;
    start_render_threads(&thread_pool, &scene);

    while (scene.is_running)
    {
        const u64 time_frame_start = time_ms();

        SDL_RenderClear(sdl_renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            handle_event(&event, &scene);
        }

        scene.mtrx             = matrix_place(scene.cams->coordinates, scene.cams->direction);
        scene.projection_coeff = scene.width / (2 * tan(scene.cams->field_of_v * 0.5 * M_PI * 0.00555555555));
        render(&thread_pool, scene.height);

        if (SDL_UpdateTexture(backbuffer_texture, 0, scene.pixels, scene.width * sizeof(int)))
        {
            printf("!SDL_UpdateTexture() error!");
            exit_rt(&scene);
        }

        SDL_RenderCopy(sdl_renderer, backbuffer_texture, 0, 0);

        SDL_RenderPresent(sdl_renderer);

        const u64 time_frame_end = time_ms();
        const u64 time_elapsed   = time_frame_end - time_frame_start;
        printf("MS: %lu -- FPS: %lu\n", time_elapsed, 1000 / time_elapsed);
    }

    destroy_render(&thread_pool);

    SDL_DestroyTexture(backbuffer_texture);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(scene.window);
    SDL_Quit();
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
