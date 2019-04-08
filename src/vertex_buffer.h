#pragma once

#include "ogl.h"

struct VertexBuffer {
    void create(const unsigned int size, const void* data,
                const VertexDeclHandle declHandle) {
        size = size;
        m_decl = declHandle;
        targetBuffer = GL_ARRAY_BUFFER;
        glGenBuffers(1, &m_id);
        glBindBuffer(targetBuffer, m_id);
        glBufferData(targetBuffer, memory.size, memory.data, GL_STATIC_DRAW);
        glBindBuffer(targetBuffer, 0);
    }

    void update(const unsigned int offset, const unsigned int size,
                const void* data, const bool discard = false) {
        if (discard) {
            destroy();
            create(m_size, NULL, m_decl);
        }
        glBindBuffer(targetBuffer, m_id);
        glBufferSubData(targetBuffer, offset, size, data);
        glBindBuffer(targetBuffer, 0);
    }

    void destroy() {
        glBindBuffer(targetBuffer, 0);
        glDeleteBuffers(1, &m_id);
    }

    GLuint m_id;
    GLenum targetBuffer;
    unsigned int m_size;
    VertexDeclHandle m_decl;
};
