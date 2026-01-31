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
    Transform *transform = malloc(sizeof(Transform));
    if (!transform)
        return NULL;

    transform->base.type = COMPONENT_TRANSFORM;
    transform->base.update = Transform_Update;

    transform->x = x;
    transform->y = y;
    transform->scaleX = 1.0f;
    transform->scaleY = 1.0f;

    transform->base.owner = NULL;

    return transform;
}
