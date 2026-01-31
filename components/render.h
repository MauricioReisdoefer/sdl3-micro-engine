#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include "component.h"
#include "color.h"

typedef struct RenderComponent
{
    Component base;

    SDL_Renderer *renderer;
    float width;
    float height;

    Color color;
} RenderComponent;

void Render_Update(Component *self, float dt);

RenderComponent *Render_Create(
    SDL_Renderer *renderer,
    float width,
    float height,
    Color color);

#endif