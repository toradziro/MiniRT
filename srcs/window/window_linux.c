#include "window.h"
#include "../includes/MiniRT.h"
#ifdef MAC_OS
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_render.h>
#include <SDL_video.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#endif

typedef struct s_platform_window
{
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Texture*  texture;
} t_platform_window;

t_key convert_sdl_key_to_inner(SDL_Keysym key)
{
    switch (key.scancode)
    {
    case (SDL_SCANCODE_TAB):
        return RT_SCANCODE_TAB;
    case (SDL_SCANCODE_W):
        return RT_SCANCODE_W;
    case (SDL_SCANCODE_S):
        return RT_SCANCODE_S;
    case (SDL_SCANCODE_A):
        return RT_SCANCODE_A;
    case (SDL_SCANCODE_D):
        return RT_SCANCODE_D;
    case (SDL_SCANCODE_E):
        return RT_SCANCODE_E;
    case (SDL_SCANCODE_Q):
        return RT_SCANCODE_Q;
    case (SDL_SCANCODE_ESCAPE):
        return RT_SCANCODE_ESCAPE;
    case (SDL_SCANCODE_UP):
        return RT_SCANCODE_ARROW_UP;
    case (SDL_SCANCODE_DOWN):
        return RT_SCANCODE_ARROW_DOWN;
    case (SDL_SCANCODE_LEFT):
        return RT_SCANCODE_ARROW_LEFT;
    case (SDL_SCANCODE_RIGHT):
        return RT_SCANCODE_ARROW_RIGHT;
    case (SDL_SCANCODE_RETURN):
        return RT_SCANCODE_ENTER;
    default:
        break;
    }
    return NONE;
}

void handle_event(SDL_Event* event, t_application* application)
{
    switch (event->type)
    {
    case SDL_QUIT:
    {
        application->is_running = false;
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
        press_key(convert_sdl_key_to_inner(event->key.keysym), application);
    }
    break;
    }
}

t_window create_window(const char* name, i32 width, i32 height, t_memory_arena* arena)
{
    t_window           window;
    t_platform_window* pl_window = arena_push(arena, sizeof(t_platform_window));
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //-- TODO: Add new error
        killed_by_error(MALLOC_ERROR);
    }
    pl_window->window   = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                           /*SDL_WINDOW_RESIZABLE*/ 0);
    pl_window->renderer = SDL_CreateRenderer(pl_window->window, -1, 0);
    //-- TODO: recreate on window resize
    pl_window->texture =
        SDL_CreateTexture(pl_window->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    window.window = (void*)pl_window;
    window.height = height;
    window.width  = width;
    return window;
}

void process_events(t_window* window, t_application* application)
{
    (void)window;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handle_event(&event, application);
    }
}

void present_buffer_in_window(t_window* window)
{
    t_platform_window* pl_window = (t_platform_window*)window->window;
    SDL_SetRenderDrawColor(pl_window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(pl_window->renderer);
    if (SDL_UpdateTexture(pl_window->texture, 0, window->buffer, window->width * sizeof(int)))
    {
        printf("!SDL_UpdateTexture() error!");
    }
    SDL_RenderCopy(pl_window->renderer, pl_window->texture, 0, 0);
    SDL_RenderPresent(pl_window->renderer);
}

void destroy_window(t_window* window)
{
    t_platform_window* pl_window = (t_platform_window*)window->window;
    SDL_DestroyTexture(pl_window->texture);
    SDL_DestroyRenderer(pl_window->renderer);
    SDL_DestroyWindow(pl_window->window);
    SDL_Quit();
}
