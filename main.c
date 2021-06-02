#include <stdio.h>
#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <SDL.h>

static SDL_Renderer *gs_renderer = NULL;
static bool gs_running = false;

void main_loop(void)
{
    SDL_Rect rect = { 100, 100, 100, 100};

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                gs_running = false;
                return;

            default:
                break;
        }
    }

    SDL_SetRenderDrawColor(gs_renderer, 0, 0, 0, 255);
    SDL_RenderClear(gs_renderer);

    SDL_SetRenderDrawColor(gs_renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(gs_renderer, &rect);

    SDL_RenderPresent(gs_renderer);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("SDL Boilerplate", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 800, 0);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    gs_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    gs_running = true;
#ifndef __EMSCRIPTEN__
    while (gs_running)
    {
        main_loop();
    }
#else
    emscripten_set_main_loop(main_loop, -1, 1);
#endif

    SDL_DestroyRenderer(gs_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
