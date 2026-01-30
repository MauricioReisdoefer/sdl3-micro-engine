#ifndef TRANSFROM_H
#define TRANSFROM_H

#include "component.h"

typedef struct
{
    Component base;

    float x;
    float y;

    float scaleX;
    float scaleY;
} Transform;

#endif