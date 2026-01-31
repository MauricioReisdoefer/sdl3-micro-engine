#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "component.h"
#include "rigidbody.h"
#include "gameobject.h"

void Player_Update(Component *self, float dt)
{
    Player *player = (Player *)self;
    Rigidbody *rigidbody = (Rigidbody *)GameObject_GetComponent(player->script.base.owner, COMPONENT_RIGIDBODY);

    const bool *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_W])
        Rigidbody_AddForce(rigidbody, 0, -player->speed);
    if (keys[SDL_SCANCODE_S])
        Rigidbody_AddForce(rigidbody, 0, player->speed);
    if (keys[SDL_SCANCODE_D])
        Rigidbody_AddForce(rigidbody, player->speed, 0);
    if (keys[SDL_SCANCODE_A])
        Rigidbody_AddForce(rigidbody, -player->speed, 0);
}

Player *Player_Create(float speed)
{
    Player *Player = malloc(sizeof(Player));
    if (!Player)
        return NULL;

    Player->script.base.type = COMPONENT_SCRIPT;
    Player->script.base.update = Player_Update;

    Player->speed = speed;

    Player->script.base.owner = NULL;

    return Player;
}
