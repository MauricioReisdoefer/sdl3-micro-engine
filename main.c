#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "component.h"
#include "player.h"
#include "render.h"
#include "rigidbody.h"
#include "script.h"
#include "transform.h"
#include "gameobject.h"
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

    SDL_Window *window = SDL_CreateWindow("TEST SCRIPTS", WIDTH, HEIGHT, SDL_WINDOW_MAXIMIZED);
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

    GameObject *player = GameObject_Create();
    Transform *transform = Transform_Create(WIDTH / 2, HEIGHT / 2);
    Rigidbody *rb = Rigidbody_Create();
    Player *playerScript = Player_Create(800);
    RenderComponent *renderComponent = Render_Create(renderer, 1, 1, WHITE);

    rb->friction = 2.0f;
    rb->mass = 2.0f;

    transform->scaleX = 35.0f;
    transform->scaleY = 35.0f;

    GameObject_AddComponent(player, (Component *)transform);
    GameObject_AddComponent(player, (Component *)rb);
    GameObject_AddComponent(player, (Component *)renderComponent);

    GameObject_AddScript(player, (ScriptComponent *)playerScript);

    int running = 1;
    SDL_Event event;

    Uint64 lastTime = SDL_GetTicks();
    float deltaTime;

    while (running)
    {
        Uint64 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        GameObject_Update(player, deltaTime);
        SDL_RenderPresent(renderer);
    }
}