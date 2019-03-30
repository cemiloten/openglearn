#pragma once

#include "ogl.h"

struct VertexBuffer
{
    void create(
        const unsigned int _size,
        const void* _data,
        const VertexDeclHandle _declHandle,
        const unsigned short int _flags = 0)
    {
        m_size = _size;
        m_decl = _declHandle;
        m_target = GL_ARRAY_BUFFER;

        glGenBuffers(1, &m_id);
        glBindBuffer(m_target, m_id);
        glBufferData(
            m_target,
            _size,
            _data,
            _data == NULL ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(m_target, 0);
    }

    void update(
        const unsigned int _offset,
        const unsigned int _size,
        const void* _data,
        const bool _discard = false)
    {
        if (_discard) {
            destroy();
            create(m_size, NULL, m_decl);
        }

        glBindBuffer(m_target, m_id);
        glBufferSubData(m_target, _offset, _size, _data);
        glBindBuffer(m_target, 0);
    }

    void destroy()
    {
        glBindBuffer(m_target, 0);
        glDeleteBuffers(1, &m_id);
    }

    GLuint m_id;
    GLenum m_target;
    unsigned int m_size;
    VertexDeclHandle m_decl;
};
