#include "gameobject.h"
#include <stdlib.h>

GameObject *GameObject_Create(void)
{
    GameObject *go = malloc(sizeof(GameObject));
    if (!go)
        return NULL;

    go->componentCount = 0;
    go->active = 1;

    return go;
}