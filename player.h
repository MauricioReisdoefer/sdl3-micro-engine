#ifndef PLAYER_H
#define PLAYER_H

#include "component.h"

typedef struct
{
    Component base;

    float speed;

} Player;

void Player_Update(Component *self, float dt);
Player *Player_Create(float x, float y);

#endif