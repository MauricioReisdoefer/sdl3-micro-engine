#ifndef PLAYER_H
#define PLAYER_H

#include "script.h"

typedef struct
{
    ScriptComponent script;

    float speed;

} Player;

void Player_Update(Component *self, float dt);
Player *Player_Create(float speed);

#endif