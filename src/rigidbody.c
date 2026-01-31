#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rigidbody.h"
#include "transform.h"
#include "gameobject.h"

Rigidbody *Rigidbody_Create(void)
{
    Rigidbody *rb = malloc(sizeof(Rigidbody));

    rb->base.type = COMPONENT_RIGIDBODY;
    rb->base.update = Rigidbody_Update;
    rb->base.owner = NULL;

    rb->velocityX = 0.0f;
    rb->velocityY = 0.0f;
    rb->friction = 0.0f;

    rb->forceX = 0.0f;
    rb->forceY = 0.0f;

    return rb;
}

void Rigidbody_AddForce(Rigidbody *rb, float fx, float fy)
{
    rb->forceX += fx;
    rb->forceY += fy;
}

void Rigidbody_Update(Component *self, float dt)
{
    Rigidbody *rb = (Rigidbody *)self;

    if (!self->owner)
        return;

    Transform *transform = (Transform *)GameObject_GetComponent(
        self->owner,
        COMPONENT_TRANSFORM);

    if (!transform)
        return;

    float acelerationx = rb->forceX / rb->mass;
    float acelerationy = rb->forceY / rb->mass;

    rb->velocityX += acelerationx * dt;
    rb->velocityY += acelerationy * dt;

    transform->x += rb->velocityX * dt;
    transform->y += rb->velocityY * dt;

    float damping = 1.0f - (rb->friction * dt);
    if (damping < 0.0f)
        damping = 0.0f;

    rb->velocityX *= damping;
    rb->velocityY *= damping;

    rb->forceX = 0.0f;
    rb->forceY = 0.0f;
}