#include <stdio.h>
#include <stdlib.h>
#include "transform.h"

void Transform_Update(Component *self, float dt)
{
    Transform *transform = (Transform *)self;
    (void)dt;
}

Transform *Transform_Create(float x, float y)
{
    Transform *t = malloc(sizeof(Transform));
    if (!t)
        return NULL;

    t->base.type = COMPONENT_TRANSFORM;
    t->base.update = Transform_Update;

    t->x = x;
    t->y = y;
    t->scaleX = 1.0f;
    t->scaleY = 1.0f;

    return t;
}
