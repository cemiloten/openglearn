#pragma once

enum class ComponentType : unsigned int
{
    None       = 0,
    Transform  = 1 << 0,
    Mesh       = 1 << 1,
};

struct IComponent
{
public:
    virtual ComponentType get_type() const = 0;
};