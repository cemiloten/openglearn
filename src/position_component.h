#pragma once

#include "component.h"
#include "vector3.h"

struct Position: public Component
{
    float x;
    float y;
    float z;

    Position(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {}

    Position(Vector3 position)
        : x(position.x), y(position.y), z(position.z)
    {}

    ComponentType GetType() override
    {
        return CompTypePosition;
    }
};