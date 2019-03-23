#pragma once

enum ComponentType
{
    CompTypeNone      = 0,
    CompTypePosition  = 1 << 0,
    CompTypeRotation  = 1 << 1,
    // = 1 << 2,
    // = 1 << 3,
    // = 1 << 4,
    // = 1 << 5,
    // = 1 << 6,
};

struct Component
{
    virtual ComponentType GetType() = 0;
};