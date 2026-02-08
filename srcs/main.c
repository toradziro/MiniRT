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
#include "includes/parser.h"
#include "includes/threads.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <x86intrin.h>
#include <stdio.h>

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
   	// mlx_hook(scene->window, 4, 0, mouse_press, scene);
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
	t_scene		*scene;
	int			fd;

	if (argc != 2 && argc != 3)
		killed_by_error(INV_AM_OF_ARG);
	check_valid_name(argv[1]);
	scene = ft_init_scene();
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
	    //-- TODO: Add new error
		killed_by_error(MALLOC_ERROR);
	}
	fd = open(argv[1], O_RDONLY);
	start_parse(scene, fd);
	check_scene(scene);
	SDL_Window *sdl_window = SDL_CreateWindow("MiniRT",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              scene->width,
                              scene->height,
                              /*SDL_WINDOW_RESIZABLE*/ 0);
	scene->window = sdl_window;

	if (argc == 3 && !strcmp(argv[2], "--save"))
	{
		scene->is_save = 1;
	}
	else if (argc == 3 && strcmp(argv[2], "--save"))
	{
		killed_by_error(UNKNWN_ARG);
	}

	//-- TODO: change to mmap
	scene->pixels = malloc(scene->width * scene->height * sizeof(int));
	SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
	//-- TODO: recreate on window resize
	SDL_Texture* backbuffer_texture = SDL_CreateTexture(sdl_renderer,
                                         SDL_PIXELFORMAT_ARGB8888,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         scene->width,
                                         scene->height);

	scene->is_running = true;
	while (scene->is_running)
	{
	    const u64 clocks_start = __rdtsc();
		const u64 time_frame_start = time_ms();

		SDL_RenderClear(sdl_renderer);
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            handle_event(&event, scene);
        }
    	threads(scene);

        if (SDL_UpdateTexture(backbuffer_texture,
                            0,
                            scene->pixels,
                            scene->width * sizeof(int)))
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
	free_scene(scene);
	SDL_DestroyTexture(backbuffer_texture);
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(scene->window);
	return (0);
}

void			start_parse(t_scene *scene, int fd)
{
	char		*line;
	char		*tmp;

	while (get_next_line(fd, &line))
	{
		if (!line[0] || line[0] == '#')
		{
			free(line);
			continue ;
		}
		tmp = line;
		parser(tmp, scene);
		free(line);
	}
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
