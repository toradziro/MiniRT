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
#include "debug_draw/draw_line.h"
#include "debug_draw/text.h"
#include "application/application.h"
#include <stdio.h>
#include <dirent.h>

#define M_RT_PI (3.14159)

typedef struct
{
    i32 width;
    i32 height;
    void* pixels;
} t_application_window;

void create_menu_items(t_menu_state* menu_state, t_memory_arena* arena)
{
    menu_state->items = arena_push(arena, sizeof(t_menu_items_list));
    menu_state->items->next = NULL;
}

void push_next_menu_item(t_menu_items_list* curr, t_memory_arena* arena)
{
    curr->next = arena_push(arena, sizeof(t_menu_items_list));
    curr->next->next = NULL;
}

void fill_menu_state(t_menu_state* menu_state, t_memory_arena* arena)
{
    //-- TODO: move to platform layer
    const char* path = "./assets/";
    DIR *dir = opendir(path);
    if (!dir)
    {
        return;
    }

    struct dirent *entry;
    t_menu_items_list* curr = NULL;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
        {
            continue;
        }

        if (entry->d_type == DT_REG)
        {
            u8* filepath = arena_push(arena, sizeof(u8) * 1024);
            i32 fpath_length = snprintf((char*)filepath, 1024, "%s/%s", path, entry->d_name);
            i32 filename_len = strlen(entry->d_name);
            u8* filename = arena_push(arena, sizeof(u8) * filename_len);
            memcpy(filename, entry->d_name, filename_len);
            if (menu_state->items == NULL)
            {
                create_menu_items(menu_state, arena);
                menu_state->items->full_path.mem = filepath;
                menu_state->items->full_path.size = fpath_length;
                menu_state->items->filename.mem = filename;
                menu_state->items->filename.size = filename_len;
                curr = menu_state->items;
            }
            else
            {
                push_next_menu_item(curr, arena);
                curr->next->full_path.mem = filepath;
                curr->next->full_path.size = fpath_length;
                curr->next->filename.mem = filename;
                curr->next->filename.size = filename_len;
                curr = curr->next;
            }
        }
    }

    closedir(dir);
}

void update_menu(t_menu_state* menu_state, t_application_window* window)
{
    i32 curr = 0;
    t_color selected_item_color = { 255, 255, 255 };
    t_color idle_item_color = { 255, 0, 0 };

    iv2 text_pos = { 10, 20 };
    t_menu_items_list* curr_item = menu_state->items;
    memcpy(window->pixels, menu_state->menu_background, window->width * window->height * sizeof(i32));
    while (curr_item)
    {
        draw_debug_text(
            curr_item->filename,
            text_pos,
            curr == menu_state->selected_item ? selected_item_color : idle_item_color,
            6.0f,      // Overall scale. Default to 1.0f
            6.0f,      // Width. Default to 1.0f
            6.0f,     // Height. Default to 1.0f
            0.0f,    // Character Spacing. Default to 0.0f
            1.0f,
            window->width,
            window->height,
            window->pixels);
        curr_item = curr_item->next;
        text_pos.y += 40;
        curr++;
    }
}

str8 curr_selected_menu_item(t_application* application)
{
    i32 curr = 0;
    t_menu_items_list* curr_item = application->menu_state.items;
    str8 res = { 0 };

    while (curr_item)
    {
        if (curr == application->menu_state.selected_item)
        {
            res = curr_item->full_path;
        }
        curr_item = curr_item->next;
        curr++;
    }
    return res;
}

void destroy_current_scene(t_application* application)
{
    if (application->curr_scene.pixels != NULL)
    {
        destroy_render(&application->curr_scene.thread_pool);
        destroy_arena(&application->curr_scene.scene_arena);
        memset(&application->curr_scene, 0, sizeof(t_scene));
    }
}

void update_scene(t_scene* scene)
{
    const float proj_coeff = 2 * tan(scene->cams->field_of_v * 0.5 * M_RT_PI * 0.00555555555);

    if (scene->need_update_mtx)
    {
        scene->mtrx = matrix_place(scene->cams);
        scene->need_update_mtx = false;
    }
    scene->projection_coeff = scene->width / proj_coeff;
    render(&scene->thread_pool, scene->height);
}

void load_scene(t_application* application, t_application_window* app_win)
{
    t_memory_arena scene_local_arena = create_arena(MB(500));
    t_scene* scene = &application->curr_scene;

    memset(scene, 0, sizeof(t_scene));
    scene->scene_arena = scene_local_arena;

    scene->pixels = app_win->pixels;

    start_parse(scene, curr_selected_menu_item(application), &scene_local_arena);
    check_scene(scene);

    assignAABB(scene->figures);
    scene->bvh = buildBVH(scene->figures->triangles, scene->figures->length, &scene_local_arena);

    scene->pixels_avg = arena_push(&scene_local_arena, app_win->width * app_win->height * sizeof(t_accum_data));
    memset(scene->pixels_avg, 0, app_win->width * app_win->height * sizeof(t_accum_data));

    start_render_threads(&scene->thread_pool, scene, &scene_local_arena);
    scene->need_update_mtx = true;
}

void blur_background(void* pixels, i32 width, i32 height, t_memory_arena* arena)
{
    i32* pixels_i = (i32*)pixels;
    i32* temp = (i32*)arena_push(arena, width * height * sizeof(i32));
    memcpy(temp, pixels_i, width * height * sizeof(i32));

    for (i32 y = 0; y < height; ++y)
    {
        for (i32 x = 0; x < width; ++x)
        {
            i32 r = 0, g = 0, b = 0, a = 0;
            i32 count = 0;

            i32 radius = 7;

            for (i32 dy = -radius; dy <= radius; ++dy)
            {
                for (i32 dx = -radius; dx <= radius; ++dx)
                {
                    i32 ny = y + dy;
                    i32 nx = x + dx;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        u32 pixel = ((u32*)temp)[ny * width + nx];
                        r += (pixel >> 16) & 0xFF;
                        g += (pixel >>  8) & 0xFF;
                        b += (pixel >>  0) & 0xFF;
                        a += (pixel >> 24) & 0xFF;
                        count++;
                    }
                }
            }

            u32 avg = ((a / count) << 24) |
                      ((r / count) << 16) |
                      ((g / count) <<  8) |
                      ((b / count) <<  0);

            ((u32*)pixels_i)[y * width + x] = avg;
        }
    }

    arena_pop(arena, width * height * sizeof(i32));
}

int main()
{
    //-- TODO: Refactor in three calls: init, run, stop
    const i32 width = 800;
    const i32 height = 600;

    t_memory_arena global_arena = create_arena(GB(1));

    t_application application;
    application.curr_app_state = Scene;
    application.scene_loading_triggered = false;
    memset(&application.curr_scene, 0, sizeof(t_scene));

    //-- Our screen buffer
    void* pixels     = arena_push(&global_arena, width * height * sizeof(i32));
    memset(pixels, 0, width * height * sizeof(i32));

    application.is_running = true;
    t_window window = create_window("MiniRT", width, height, &global_arena);
    window.buffer   = pixels;

    //-- Application window
    t_application_window app_win;
    app_win.width = width;
    app_win.height = height;
    app_win.pixels = pixels;
    memset(&application.menu_state, 0, sizeof(t_menu_state));

    //-- Init menu
    fill_menu_state(&application.menu_state, &global_arena);
    application.menu_state.menu_background = arena_push(&global_arena, width * height * sizeof(i32));
    memset(application.menu_state.menu_background, 0, width * height * sizeof(i32));

    str8 drawing_stat;
    drawing_stat.mem = arena_push(&global_arena, 100);

    load_scene(&application, &app_win);

    while (application.is_running)
    {
        const u32 time_frame_start = time_ms();
        process_events(&window, &application);
        memset(app_win.pixels, 0, (app_win.width * app_win.height * sizeof(i32)));
        switch (application.curr_app_state)
        {
            case Menu: update_menu(&application.menu_state, &app_win); break;
            case Scene: update_scene(&application.curr_scene); break;
            default: break;
        }

        if (application.switch_to_menu_triggered)
        {
            memcpy(application.menu_state.menu_background, application.curr_scene.pixels, width * height * sizeof(i32));
            blur_background(application.menu_state.menu_background, width, height, &global_arena);
            application.curr_app_state = Menu;
            application.switch_to_menu_triggered = false;
        }


        if (application.scene_loading_triggered)
        {
            destroy_current_scene(&application);
            load_scene(&application, &app_win);
            application.curr_app_state = Scene;
            application.scene_loading_triggered = false;
        }

        const u32 time_frame_end = time_ms();
        const u32 time_elapsed   = time_frame_end - time_frame_start;
        drawing_stat.size = snprintf((char*)drawing_stat.mem, 100, "MS:%u FPS:%u", time_elapsed, 1000 / time_elapsed);
        iv2 text_pos = { 630, 570 };
        t_color color = { 255.0f, 0, 0 };
        draw_debug_text(
            drawing_stat,
            text_pos,
            color,
            5.0f,      // Overall scale. Default to 1.0f
            5.0f,      // Width. Default to 1.0f
            5.0f,     // Height. Default to 1.0f
            0.0f,    // Character Spacing. Default to 0.0f
            1.0f,
            app_win.width,
            app_win.height,
            app_win.pixels);
        application.curr_scene.dt = (float)time_elapsed / 1000.0f;

        present_buffer_in_window(&window);
    }
    destroy_current_scene(&application);
    destroy_window(&window);
    destroy_arena(&global_arena);

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
