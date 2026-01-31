#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "component.h"

typedef struct
{
    Component base;

    float velocityX;
    float velocityY;

    float forceX;
    float forceY;

    float mass;
    float friction;

} Rigidbody;

void Rigidbody_Update(Component *self, float dt);
Rigidbody *Rigidbody_Create(void);
void Rigidbody_AddForce(Rigidbody *rb, float fx, float fy);

#endif