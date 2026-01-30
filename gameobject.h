#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"

#define MAX_COMPONENTS 16

typedef struct GameObject
{
    Component *components[MAX_COMPONENTS];
    int componentCount;
    int active;
} GameObject;

GameObject *GameObject_Create(void);

#endif
