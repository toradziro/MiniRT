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

#include "includes/MiniRT.h"
#include "arena/arena.h"
#include "includes/my_types.h"
#include "includes/parser.h"
#include "includes/threads.h"
# include "arena/arena.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <x86intrin.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct s_primitives_amount
{
    i32 lights_count;
    i32 figures_count;
    i32 cams_count;
} t_primitives_amount;

void handle_event(SDL_Event* event, t_scene* scene)
{
    switch(event->type)
    {
        case SDL_QUIT:
        {
            exit_rt(scene);
        } break;

        case SDL_WINDOWEVENT:
        {
            switch(event->window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                {
                } break;
            }
        } break;
        case SDL_KEYDOWN:
        {
           	press_key(event->key.keysym, scene);
        } break;
    }
}

u64 time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000 +
           (u64)ts.tv_nsec / 1000000;
}

int				main(int argc, char **argv)
{
    t_memory_arena  global_arena = create_arena(GB(1));
	t_scene		    scene;

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
	SDL_Window *sdl_window = SDL_CreateWindow("MiniRT",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              scene.width,
                              scene.height,
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
	scene.pixels = malloc(scene.width * scene.height * sizeof(int));
	SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
	//-- TODO: recreate on window resize
	SDL_Texture* backbuffer_texture = SDL_CreateTexture(sdl_renderer,
                                         SDL_PIXELFORMAT_ARGB8888,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         scene.width,
                                         scene.height);

	scene.is_running = true;
	while (scene.is_running)
	{
	    const u64 clocks_start = __rdtsc();
		const u64 time_frame_start = time_ms();

		SDL_RenderClear(sdl_renderer);
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            handle_event(&event, &scene);
        }
        //-- TODO: Rename to render
    	threads(&scene);

        if (SDL_UpdateTexture(backbuffer_texture,
                            0,
                            scene.pixels,
                            scene.width * sizeof(int)))
        {
            //-- TODO: Do something about this error!
            printf("!SDL_UpdateTexture() error!");
        }

        SDL_RenderCopy(sdl_renderer,
                       backbuffer_texture,
                       0,
                       0);

        SDL_RenderPresent(sdl_renderer);

        const u64 time_frame_end = time_ms();
        const u64 time_elapsed = time_frame_end - time_frame_start;
        const u64 clocks_end = __rdtsc();
        printf("MCl: %lu -- MS: %lu -- FPS: %lu\n", (clocks_end - clocks_start) / 1000, time_elapsed, 1000 / time_elapsed);
	}
	SDL_DestroyTexture(backbuffer_texture);
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(scene.window);
	destroy_arena(&global_arena);
	return (0);
}

typedef struct s_str8
{
    u32     size;
    u8*     mem;
} str8;

str8 read_full_file(const char *path)
{
    int fd = open(path, O_RDONLY);

    str8 ret;
    ret.mem = NULL;
    ret.size = 0;

    if (fd < 0)
    {
        printf("Error opening a file read_full_file %s", path);
        return ret;
    }

    struct stat st;
    fstat(fd, &st);

    ret.mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    ret.size = st.st_size;
    close(fd);

    if (ret.mem == MAP_FAILED)
    {
        printf("Error opening a file read_full_file %s", path);
        return ret;
    }

    return ret;
}

void clean_file(str8* file)
{
    munmap(file->mem, file->size);
    file->mem = NULL;
    file->size = 0;
}

str8 get_next_line(str8 file, u32* curr, t_memory_arena* arena)
{
    str8 out = {0, NULL};

    if (!curr || !arena || *curr >= file.size)
        return out; // EOF / invalid

    u32 start = *curr;
    u32 i = start;

    //-- find end of line
    while (i < file.size && file.mem[i] != '\n')
    {
        i++;
    }

    //-- len without '\n'
    u32 len = i - start;

    //-- win capable
    if (len > 0 && file.mem[start + len - 1] == '\r')
        len--;

    //-- we want \0 so we need allocation
    //-- TODO: Switch api on size in str8
    u8* dst = (u8*)arena_push(arena, len + 1);
    if (!dst)
    {
        return out;
    }

    // copy
    if (len > 0)
    {
        memcpy(dst, file.mem + start, len);
    }

    dst[len] = 0;

    out.mem = dst;
    out.size = len;

    // move cursor after \n
    if (i < file.size && file.mem[i] == '\n')
    {
        i++;
    }

    *curr = i;
    return out;
}

void			start_parse(t_scene *scene, const char* path, t_memory_arena* arena)
{
	str8        file;
	arena = arena;

	t_primitives_amount amount;
	amount.cams_count = 0;
	amount.lights_count = 0;
	amount.figures_count = 0;

	//-- Read full file
	file = read_full_file(path);
	u32 curr = 0;
	while (curr < file.size)
	{
	    str8 line = get_next_line(file, &curr, arena);
		if (!line.mem[0] || line.mem[0] == '#')
		{
			continue;
		}

        if (line.mem[0] == 'c' && line.mem[1] == 'y')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 'c')
        {
            ++amount.cams_count;
        }
        else if (line.mem[0] == 'l')
        {
            ++amount.lights_count;
        }
        else if (line.mem[0] == 's' && line.mem[1] == 'p')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 'p' && line.mem[1] == 'l')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 's' && line.mem[1] == 'q')
        {
            ++amount.figures_count;
        }
        else if (line.mem[0] == 't' && line.mem[1] == 'r')
        {
            ++amount.figures_count;
        }
        arena_pop(arena, line.size);
	}

	// preallocate_memory();

	curr = 0;
	while (curr < file.size)
	{
	    str8 line = get_next_line(file, &curr, arena);
		if (!line.mem[0] || line.mem[0] == '#')
		{
			continue ;
		}
		parser((char*)line.mem, scene);
		arena_pop(arena, line.size);
	}

	clean_file(&file);
}

int				exit_rt(t_scene *scene)
{
    scene->is_running = false;
	return (0);
}

void			check_scene(t_scene *scene)
{
	if (!scene->is_amb_l || !scene->is_cam ||
		!scene->is_figur || !scene->is_light || !scene->is_size)
		killed_by_error(NOT_ENOUGH);
}
