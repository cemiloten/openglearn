#pragma once

#include <limits>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct IHandle {
    unsigned short int index;

    bool is_valid(IHandle _handle) {
        return _handle.index != IHandle::invalid_handle;
    }

  private:
    const static unsigned short int invalid_handle =
        std::numeric_limits<unsigned short int>::max();
};

struct IndexBufferHandle : public IHandle {};
struct VertexBufferHandle : public IHandle {};
struct VertexDeclHandle : public IHandle {};
