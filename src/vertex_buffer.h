#pragma once

#include "ogl.h"

struct VertexBuffer {
    void create(const unsigned int size, const void* data,
                const VertexDeclHandle declHandle) {
    }

    void update(const unsigned int offset, const unsigned int size,
                const void* data, const bool discard = false) {
    }

    void destroy() {
    }

    GLuint _id;
    GLenum _targetBuffer;
    unsigned int _size;
};
