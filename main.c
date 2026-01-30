
#include <stdio.h>

#include <stdlib.h>

#include "gameobject.h"
#include "transform.h"

int main(void)
{
    // Cria um GameObject
    GameObject *player = GameObject_Create();
    if (!player)
    {
        printf("Erro ao criar GameObject\n");
        return 1;
    }

    // Cria um Transform
    Transform *transform = Transform_Create(100.0f, 200.0f);
    if (!transform)
    {
        printf("Erro ao criar Transform\n");
        return 1;
    }

    // Adiciona o Transform ao GameObject
    GameObject_AddComponent(player, (Component *)transform);

    // Recupera o Transform pelo sistema de componentes
    Transform *t = (Transform *)GameObject_GetComponent(
        player, COMPONENT_TRANSFORM);

    if (t)
    {
        printf("GameObject criado com sucesso\n");
        printf("Posicao: x = %.2f | y = %.2f\n", t->x, t->y);
        printf("Scale:   x = %.2f | y = %.2f\n", t->scaleX, t->scaleY);
    }
    else
    {
        printf("Transform nao encontrado\n");
    }

    free(transform);
    free(player);

    return 0;
}