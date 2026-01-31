# Documentação da sdl3-micro-engine

## 1. Introdução

A `sdl3-micro-engine` é uma *micro-engine* de jogos minimalista escrita em C, projetada para demonstrar os princípios de uma arquitetura baseada em componentes (*Entity-Component-System* - ECS) utilizando a biblioteca SDL3. Seu principal objetivo é fornecer uma estrutura simples e extensível para o desenvolvimento de jogos 2D, focando na separação de dados e lógica através de componentes.

## 2. Estrutura da Engine

A engine é construída em torno de dois conceitos centrais: o `GameObject` e o `Component`.

### 2.1. O Conceito de GameObject

O `GameObject` é a entidade fundamental no mundo do jogo. Ele não contém lógica de jogo por si só, mas atua como um contêiner para diversos `Componentes`.

```c
typedef struct GameObject
{
    Component *components[MAX_COMPONENTS];
    int componentCount;
    int active;
} GameObject;
```

### 2.2. O Sistema de Componentes

Um `Component` define uma característica ou comportamento que pode ser anexado a um `GameObject`. Todos os componentes herdam da estrutura base `Component`.

```c
typedef struct Component
{
    ComponentType type;
    ComponentUpdateFunction update;
    GameObject *owner;
} Component;
```

O campo `type` é usado para identificar o componente, e `update` é um ponteiro para a função que será executada a cada *frame* do jogo.

Os tipos de componentes pré-definidos são:

| Tipo de Componente | Enumeração | Descrição |
| :--- | :--- | :--- |
| Transform | `COMPONENT_TRANSFORM` | Gerencia a posição (`x`, `y`) e escala (`scaleX`, `scaleY`) do `GameObject`. |
| Rigidbody | `COMPONENT_RIGIDBODY` | Gerencia a física, como velocidade, força, massa e fricção. |
| Render | `COMPONENT_RENDER` | Responsável por desenhar o `GameObject` na tela. |
| Script | `COMPONENT_SCRIPT` | Permite anexar lógica de jogo personalizada (scripts) ao `GameObject`. |

### 2.3. O Loop Principal

O ciclo de vida da engine é gerenciado no `main.c`. Após a inicialização do SDL e a criação dos objetos e componentes, o *loop* principal executa as seguintes etapas a cada *frame*:

1. Cálculo do `deltaTime` (tempo decorrido desde o último *frame*).
2. Processamento de eventos do SDL (e.g., fechar janela, entrada do usuário).
3. Limpeza da tela (`SDL_RenderClear`).
4. Atualização de todos os componentes do `GameObject` através de `GameObject_Update`.
5. Apresentação do *frame* na tela (`SDL_RenderPresent`).

## 3. APIs Base do GameObject

As seguintes funções são a interface principal para interagir com as entidades do jogo:

| Função | Assinatura | Descrição |
| :--- | :--- | :--- |
| `GameObject_Create` | `GameObject *GameObject_Create(void)` | Cria e inicializa um novo `GameObject`. |
| `GameObject_Destroy` | `void GameObject_Destroy(GameObject *go)` | Libera a memória alocada para o `GameObject` e seus componentes. |
| `GameObject_AddComponent` | `void GameObject_AddComponent(GameObject *go, Component *component)` | Anexa um `Component` ao `GameObject`. O componente recebe uma referência ao seu `owner`. |
| `GameObject_GetComponent` | `Component *GameObject_GetComponent(GameObject *go, ComponentType type)` | Retorna o primeiro `Component` do tipo especificado anexado ao `GameObject`. |
| `GameObject_Update` | `void GameObject_Update(GameObject *go, float dt)` | Chama a função `update` de todos os componentes ativos do `GameObject`. |
| `GameObject_AddScript` | `void GameObject_AddScript(GameObject *gameobject, ScriptComponent *script)` | Função de conveniência para adicionar um `ScriptComponent`. |
| `GameObject_GetScript` | `Component *GameObject_GetScript(GameObject *gameobject, TypeID type)` | Retorna um `ScriptComponent` específico baseado no seu `TypeID`. |

## 4. Componentes Essenciais

### 4.1. Transform

Gerencia a posição e escala.

| Campo | Tipo | Descrição |
| :--- | :--- | :--- |
| `x`, `y` | `float` | Posição do objeto no espaço 2D. |
| `scaleX`, `scaleY` | `float` | Escala do objeto. |

**API:**

* `Transform *Transform_Create(float x, float y)`: Cria um novo componente `Transform` na posição inicial (`x`, `y`).
* `void Transform_Update(Component *self, float dt)`: Função de atualização (atualmente vazia, pois a lógica de movimento é tratada pelo `Rigidbody`).

### 4.2. Rigidbody

Gerencia a simulação física.

| Campo | Tipo | Descrição |
| :--- | :--- | :--- |
| `velocityX`, `velocityY` | `float` | Velocidade atual do objeto. |
| `forceX`, `forceY` | `float` | Força acumulada a ser aplicada no próximo *frame*. |
| `mass` | `float` | Massa do objeto, usada no cálculo da aceleração. |
| `friction` | `float` | Fator de fricção para desacelerar o objeto. |

**API:**

* `Rigidbody *Rigidbody_Create(void)`: Cria um novo componente `Rigidbody` com valores padrão.
* `void Rigidbody_Update(Component *self, float dt)`: Aplica forças, calcula nova velocidade e atualiza a posição do `Transform` do objeto.
* `void Rigidbody_AddForce(Rigidbody *rb, float fx, float fy)`: Adiciona uma força (`fx`, `fy`) ao `Rigidbody`.

### 4.3. RenderComponent

Gerencia a representação visual do objeto.

| Campo | Tipo | Descrição |
| :--- | :--- | :--- |
| `renderer` | `SDL_Renderer *` | O *renderer* do SDL usado para desenhar. |
| `width`, `height` | `float` | Dimensões do objeto a ser desenhado. |
| `color` | `Color` | Cor do objeto (estrutura simples com `r, g, b, a`). |

**API:**

* `RenderComponent *Render_Create(SDL_Renderer *renderer, float width, float height, Color color)`: Cria um novo componente de renderização.
* `void Render_Update(Component *self, float dt)`: Desenha um retângulo na posição e escala do `Transform` do objeto, usando a cor definida.

## 5. Sistema de Scripting (ScriptComponent)

O `ScriptComponent` é a forma de adicionar lógica de jogo personalizada. Ele herda da estrutura base `Component` e adiciona um campo crucial: `typeID`.

```c
typedef struct ScriptComponent
{
    Component base;
    TypeID typeID; // Usado para identificar o tipo de script
} ScriptComponent;
```

### 5.1. Como Criar um Script

Para criar um script (e.g., `Player`), siga os seguintes passos:

#### Passo 1: Definir a Estrutura do Script (`player.h`)

Crie uma nova estrutura que **inclua** o `ScriptComponent` como seu primeiro membro. Adicione quaisquer variáveis de estado que o script necessite (e.g., `speed`).

```c
// components/player.h
typedef struct
{
    ScriptComponent script; // Deve ser o primeiro membro
    float speed;
} Player;

void Player_Update(Component *self, float dt);
Player *Player_Create(float speed);
```

#### Passo 2: Implementar a Lógica (`player.c`)

Implemente a função de atualização (`Player_Update`) e a função de criação (`Player_Create`).

1. **Função de Criação (`Player_Create`):**
    * Aloca memória para a estrutura do script.
    * Define o tipo base como `COMPONENT_SCRIPT`.
    * Define o ponteiro de função `update` para a sua função de lógica (`Player_Update`).
    * Inicializa as variáveis de estado (e.g., `speed`).

    ```c
    // components/player.c (trecho)
    Player *Player_Create(float speed)
    {
        Player *Player = malloc(sizeof(Player));
        // ...
        Player->script.base.type = COMPONENT_SCRIPT;
        Player->script.base.update = Player_Update;
        Player->speed = speed;
        // ...
        return Player;
    }
    ```

2. **Função de Atualização (`Player_Update`):**
    * Converte o ponteiro `Component *self` de volta para o tipo de script (`Player *`).
    * Use `GameObject_GetComponent` para acessar outros componentes do mesmo `GameObject` (e.g., `Rigidbody` para aplicar movimento).
    * Implemente a lógica do jogo (e.g., ler entrada do teclado e aplicar força).

    ```c
    // components/player.c (trecho)
    void Player_Update(Component *self, float dt)
    {
        Player *player = (Player *)self;
        Rigidbody *rigidbody = (Rigidbody *)GameObject_GetComponent(player->script.base.owner, COMPONENT_RIGIDBODY);

        // Exemplo de lógica: aplicar força baseada na entrada do teclado
        const bool *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W])
            Rigidbody_AddForce(rigidbody, 0, -player->speed);
        // ...
    }
    ```

#### Passo 3: Anexar o Script ao GameObject (`main.c`)

Use a função `GameObject_AddScript` para anexar a instância do script ao `GameObject`.

```c
// main.c (trecho)
Player *playerScript = Player_Create(800);
// ...
GameObject_AddScript(player, (ScriptComponent *)playerScript);
```

Este sistema permite que a lógica de jogo seja completamente modularizada e separada dos dados do `GameObject`, seguindo o padrão ECS.
