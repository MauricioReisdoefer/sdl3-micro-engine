#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "components/component.h"
#include "color.h"

const int HEIGHT = 500;
const int WIDTH = 750;

const Color WHITE = {255, 255, 255, 255};
const Color BLACK = {0, 0, 0, 255};

int main(void)
{
    // SDL INITIALIZATION
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error on initializing SDL_VIDEO");
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("BULLET HELL", WIDTH, HEIGHT, SDL_WINDOW_MAXIMIZED);
    if (window == NULL)
    {
        SDL_Log("Error on initializing SDL_Window");
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        SDL_Log("Error on initializing SDL_Renderer");
        return -1;
    }
}