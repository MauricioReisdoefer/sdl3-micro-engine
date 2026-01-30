#include "gameobject.h"
#include <stdlib.h>

GameObject *GameObject_Create(void)
{
    GameObject *gameobject = malloc(sizeof(GameObject));
    if (!gameobject)
        return NULL;

    gameobject->componentCount = 0;
    gameobject->active = 1;

    for (int i = 0; i < MAX_COMPONENTS; i++)
        gameobject->components[i] = NULL;

    return gameobject;
}

void GameObject_AddComponent(GameObject *gameobject, Component *component)
{
    if (!gameobject || !component)
        return;

    if (gameobject->componentCount >= MAX_COMPONENTS)
        return;

    component->owner = gameobject;
    gameobject->components[gameobject->componentCount++] = component;
}

Component *GameObject_GetComponent(GameObject *gameobject, ComponentType type)
{
    if (!gameobject)
        return NULL;

    for (int i = 0; i < gameobject->componentCount; i++)
    {
        if (gameobject->components[i]->type == type)
            return gameobject->components[i];
    }

    return NULL;
}

void GameObject_Update(GameObject *gameobject, float dt)
{
    if (!gameobject || !gameobject->active)
        return;

    for (int i = 0; i < gameobject->componentCount; i++)
    {
        Component *component = gameobject->components[i];
        if (component && component->update)
        {
            component->update(component, dt);
        }
    }
}

void GameObject_Destroy(GameObject *gameobject)
{
    if (!gameobject)
        return;

    for (int i = 0; i < gameobject->componentCount; i++)
    {
        free(gameobject->components[i]);
    }

    free(gameobject);
}