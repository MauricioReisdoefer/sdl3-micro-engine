#include "component.h"

typedef const void *TypeID;

typedef struct ScriptComponent
{
    Component base;
    TypeID typeID;
} ScriptComponent;
