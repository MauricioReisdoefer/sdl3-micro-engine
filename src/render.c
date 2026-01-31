#include "render.h"
#include "gameobject.h"
#include "transform.h"
#include <stdlib.h>

void Render_Update(Component *self, float dt)
{
    (void)dt;

    RenderComponent *render = (RenderComponent *)self;
    GameObject *owner = self->owner;

    if (!owner)
        return;

    Transform *transform = (Transform *)
        GameObject_GetComponent(owner, COMPONENT_TRANSFORM);

    if (!transform)
        return;

    SDL_FRect rect = {
        transform->x,
        transform->y,
        render->width * transform->scaleX,
        render->height * transform->scaleY};

    SDL_SetRenderDrawColor(
        render->renderer,
        (Uint8)render->color.red,
        (Uint8)render->color.green,
        (Uint8)render->color.blue,
        (Uint8)render->color.alpha);

    SDL_RenderFillRect(render->renderer, &rect);
}

RenderComponent *Render_Create(
    SDL_Renderer *renderer,
    float width,
    float height,
    Color color)
{
    RenderComponent *render = malloc(sizeof(RenderComponent));
    if (!render)
        return NULL;

    render->base.type = COMPONENT_RENDER;
    render->base.update = Render_Update;
    render->base.owner = NULL;

    render->renderer = renderer;
    render->width = width;
    render->height = height;
    render->color = color;

    return render;
}