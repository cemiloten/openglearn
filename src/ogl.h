#pragma once

#include <limits>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

struct IHandle {
   public:
    unsigned int index;

    bool isValid(IHandle handle) {
        return handle.index != IHandle::invalidHandle;
    }

   private:
    const static unsigned int invalidHandle =
        std::numeric_limits<unsigned int>::max();
};

struct IndexBufferHandle : public IHandle {};
struct VertexBufferHandle : public IHandle {};

struct VertexDeclHandle : public IHandle {};
