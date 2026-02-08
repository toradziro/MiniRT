#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *Window = SDL_CreateWindow("Handmade Hero",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              SDL_WINDOW_RESIZABLE);

    for(;;)
    {
        SDL_Event Event;
        SDL_WaitEvent(&Event);
    }

    SDL_DestroyWindow(Window);
}
