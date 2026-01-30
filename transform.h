#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"

typedef struct
{
    Component base;

    float x;
    float y;

    float scaleX;
    float scaleY;
} Transform;

void Transform_Update(Component *self, float dt);
Transform *Transform_Create(float x, float y);

#endif