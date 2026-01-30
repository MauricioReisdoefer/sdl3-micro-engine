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
void GameObject_AddComponent(GameObject *go, Component *component);
Component *GameObject_GetComponent(GameObject *go, ComponentType type);
void GameObject_Update(GameObject *go, float dt);
void GameObject_Destroy(GameObject *go);

#endif
