#pragma once

#include "ogl.h"

struct VertexBuffer
{
    void create(uint32_t _size,
                void* _data,
                VertexDeclHandle _declHandle,
                unsigned int _flags = 0)
        : m_size(_size),
          m_decl(_declHandle)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(m_target, m_id);
        //glBufferData(TODO Here)
        glBindBuffer(m_target, 0);
    }

    GLuint m_id;
    // GLenum m_target;
    uint32_t m_size;
    VertexDeclHandle m_decl;
};
