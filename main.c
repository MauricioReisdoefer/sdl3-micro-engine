#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "gameobject.h"
#include "transform.h"
#include "rigidbody.h"
#include "color.h"
#include "render.h"

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

    // GAMEOBJECT INITIALIZATION
    GameObject *gameObject = GameObject_Create();
    Transform *transform = Transform_Create(0, 0);
    Rigidbody *rigidbody = Rigidbody_Create();

    GameObject_AddComponent(gameObject, (Component *)transform);
    GameObject_AddComponent(gameObject, (Component *)rigidbody);

    Transform *transformObject = (Transform *)GameObject_GetComponent(gameObject, COMPONENT_TRANSFORM);
    transformObject->scaleX = 25.0f;
    transformObject->scaleY = 25.0f;

    rigidbody->mass = 1.0f;
    rigidbody->friction = 7.0f;

    // GAME LOOP
    int isRunning = 1;

    SDL_Event event;

    Uint64 lastTime = SDL_GetTicks();
    float deltaTime;

    while (isRunning)
    {
        Uint64 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                isRunning = 0;
        }

        GameObject_Update(gameObject, deltaTime);

        SetRenderColor(renderer, &BLACK);
        SDL_RenderClear(renderer);

        SetRenderColor(renderer, &WHITE);
        RenderTransform(renderer, transform);
        SDL_RenderPresent(renderer);
    }
}