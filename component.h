#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct GameObject GameObject;
typedef struct Component Component;

typedef void (*ComponentUpdateFunction)(Component *self, float dt);

typedef enum
{
    COMPONENT_TRANSFORM,
    COMPONENT_RIGIDBODY,
    COMPONENT_RENDER,
    COMPONENT_PLAYER
} ComponentType;

typedef struct Component
{
    ComponentType type;
    ComponentUpdateFunction update;
    GameObject *owner;
} Component;

#endif