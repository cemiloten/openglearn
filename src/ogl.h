#pragma once

#include <limits>

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
