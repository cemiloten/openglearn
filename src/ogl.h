#pragma once

#include <limits>

struct IHandle
{
    unsigned short int index;

    static bool is_valid(IHandle _handle)
    {
        return _handle.index != IHandle::invalid_handle;
    }

private:
    const static unsigned short int invalid_handle = std::numeric_limits<unsigned short int>::max();
};

struct VertexDeclHandle : private IHandle {};
