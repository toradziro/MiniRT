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
#include "includes/array.h"
#include "includes/figures.h"
#include "includes/my_types.h"
#include "includes/parser.h"
#include "includes/threads.h"
#include "includes/vectors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <x86intrin.h>
#include <stdlib.h>
#include <assert.h>

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

void assignAABB(t_vec_fig* figures)
{
    const float C_EPSILON = 0.0001f;

    for (int i = 0; i < figures->length; ++i)
    {
        float max_x = MAX(MAX(figures->triangles[i].a.v_x, figures->triangles[i].b.v_x), figures->triangles[i].c.v_x);
        float max_y = MAX(MAX(figures->triangles[i].a.v_y, figures->triangles[i].b.v_y), figures->triangles[i].c.v_y);
        float max_z = MAX(MAX(figures->triangles[i].a.v_z, figures->triangles[i].b.v_z), figures->triangles[i].c.v_z);

        float min_x = MIN(MIN(figures->triangles[i].a.v_x, figures->triangles[i].b.v_x), figures->triangles[i].c.v_x);
        float min_y = MIN(MIN(figures->triangles[i].a.v_y, figures->triangles[i].b.v_y), figures->triangles[i].c.v_y);
        float min_z = MIN(MIN(figures->triangles[i].a.v_z, figures->triangles[i].b.v_z), figures->triangles[i].c.v_z);

        if (max_x - min_x < C_EPSILON)
        {
            min_x -= C_EPSILON;
            max_x += C_EPSILON;
        }
        if (max_y - min_y < C_EPSILON)
        {
            min_y -= C_EPSILON;
            max_y += C_EPSILON;
        }
        if (max_z - min_z < C_EPSILON)
        {
            min_z -= C_EPSILON;
            max_z += C_EPSILON;
        }

        figures->triangles[i].aabb.min = new_vector(min_x, min_y, min_z);
        figures->triangles[i].aabb.max = new_vector(max_x, max_y, max_z);
    }
}

t_AABB findNodeAABB(t_triangle* triangles, int count)
{
    t_AABB aabb;

    float max_x = -FLT_MAX;
    float max_y = -FLT_MAX;
    float max_z = -FLT_MAX;

    float min_x = FLT_MAX;
    float min_y = FLT_MAX;
    float min_z = FLT_MAX;

    for (int i = 0; i < count; ++i)
    {
        max_x = MAX(max_x, triangles[i].aabb.max.v_x);
        max_y = MAX(max_y, triangles[i].aabb.max.v_y);
        max_z = MAX(max_z, triangles[i].aabb.max.v_z);

        min_x = MIN(min_x, triangles[i].aabb.min.v_x);
        min_y = MIN(min_y, triangles[i].aabb.min.v_y);
        min_z = MIN(min_z, triangles[i].aabb.min.v_z);
    }

    aabb.min = new_vector(min_x, min_y, min_z);
    aabb.max = new_vector(max_x, max_y, max_z);

    return aabb;
}

typedef enum
{
    BreakingAxisX,
    BreakingAxisY,
    BreakingAxisZ,
    None
} BreakingAxis;

BreakingAxis findBreakingAxis(t_BVHNode* node)
{
    float axisXLength = node->aabb.max.v_x - node->aabb.min.v_x;
    float axisYLength = node->aabb.max.v_y - node->aabb.min.v_y;
    float axisZLength = node->aabb.max.v_z - node->aabb.min.v_z;
    BreakingAxis baxis = None;
    if (axisXLength >= axisYLength && axisXLength >= axisZLength)
    {
        baxis = BreakingAxisX;
    }
    else if (axisYLength >= axisZLength && axisYLength >= axisXLength)
    {
        baxis = BreakingAxisY;
    }
    else
    {
        baxis = BreakingAxisZ;
    }
    return baxis;
}

static BreakingAxis g_breaking_strategy;

int compareTriangles(const void *a, const void *b)
{
    t_triangle* atr = (t_triangle*)a;
    t_triangle* btr = (t_triangle*)b;
    float comparing_centroid_a = 0.0f;
    float comparing_centroid_b = 0.0f;
    switch (g_breaking_strategy)
    {
        case (BreakingAxisX):
            comparing_centroid_a = (atr->aabb.max.v_x + atr->aabb.min.v_x) * 0.5f;
            comparing_centroid_b = (btr->aabb.max.v_x + btr->aabb.min.v_x) * 0.5f;
            break;
        case (BreakingAxisY):
            comparing_centroid_a = (atr->aabb.max.v_y + atr->aabb.min.v_y) * 0.5f;
            comparing_centroid_b = (btr->aabb.max.v_y + btr->aabb.min.v_y) * 0.5f;
            break;
        case (BreakingAxisZ):
            comparing_centroid_a = (atr->aabb.max.v_z + atr->aabb.min.v_z) * 0.5f;
            comparing_centroid_b = (btr->aabb.max.v_z + btr->aabb.min.v_z) * 0.5f;
            break;
        default:
            assert(false);
            break;
    }
    if (comparing_centroid_a < comparing_centroid_b)
    {
        return -1;
    }
    else if (comparing_centroid_a > comparing_centroid_b)
    {
        return 1;
    }
    return 0;
}

void sortByAxis(BreakingAxis baxis, t_triangle* triangles, int count)
{
    g_breaking_strategy = baxis;
    qsort(triangles, count, sizeof(t_triangle), compareTriangles);
    g_breaking_strategy = None;
}

t_BVHNode* build_BVH_from_triangles(t_triangle* triangles, int count, t_memory_arena* arena)
{
    t_BVHNode* node = (t_BVHNode*)arena_push(arena, sizeof(t_BVHNode));
    node->left = NULL;
    node->right = NULL;
    node->is_leaf = false;
    node->aabb = findNodeAABB(triangles, count);

    if (count <= 4)
    {
        node->is_leaf = true;
        node->batch = triangles;
        node->count = count;
        return node;
    }

    BreakingAxis baxis = findBreakingAxis(node);
    sortByAxis(baxis, triangles, count);
    int newCount = count / 2;
    node->left = build_BVH_from_triangles(triangles, newCount, arena);
    node->right = build_BVH_from_triangles(triangles + newCount, count - newCount, arena) ;

    return node;
}

void buildBVH(t_scene* scene, t_memory_arena* arena)
{
    t_BVH bvh;
    bvh.triangles = scene->figures->triangles;
    bvh.triangle_count = scene->figures->length;
    bvh.root = build_BVH_from_triangles(bvh.triangles, bvh.triangle_count, arena);
    scene->bvh = bvh;
}

int main(int argc, char** argv)
{
    t_memory_arena global_arena = create_arena(GB(1));
    t_scene        scene;

    memset(&scene, 0, sizeof(scene));

    if (argc != 2 && argc != 3)
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
    buildBVH(&scene, &global_arena);

    SDL_Window* sdl_window =
        SDL_CreateWindow("MiniRT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scene.width, scene.height,
                         /*SDL_WINDOW_RESIZABLE*/ 0);
    scene.window = sdl_window;

    if (argc == 3 && !strcmp(argv[2], "--save"))
    {
        scene.is_save = 1;
    }
    else if (argc == 3 && strcmp(argv[2], "--save"))
    {
        killed_by_error(UNKNWN_ARG);
    }

    //-- TODO: change to mmap
    scene.pixels               = arena_push(&global_arena, scene.width * scene.height * sizeof(int));
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
        const u64 clocks_start     = __rdtsc();
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
            //-- TODO: Do something about this error!
            printf("!SDL_UpdateTexture() error!");
        }

        SDL_RenderCopy(sdl_renderer, backbuffer_texture, 0, 0);

        SDL_RenderPresent(sdl_renderer);

        const u64 time_frame_end = time_ms();
        const u64 time_elapsed   = time_frame_end - time_frame_start;
        const u64 clocks_end     = __rdtsc();
        printf("MCl: %lu -- MS: %lu -- FPS: %lu\n", (clocks_end - clocks_start) / 1000, time_elapsed,
               1000 / time_elapsed);
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
    if (!scene->is_amb_l || !scene->is_cam || !scene->is_figur || !scene->is_light || !scene->is_size)
    {
        killed_by_error(NOT_ENOUGH);
    }
}
