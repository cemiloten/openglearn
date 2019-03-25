#pragma once

#include "component.h"

struct Position: public Component
{
    float x;
    float y;
    float z;

    Position(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {}

    ComponentType GetType() override
    {
        return CompTypePosition;
    }
};