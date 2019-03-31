#pragma once

#include "ogl.h"

struct IndexBuffer
{
    void create(
        const unsigned int _size,
        const void* _data,
        const unsigned short int _flags = 0)
    {
        m_size = _size;
        m_flags = _flags;

        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            _size,
            _data,
            _data == NULL ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void update(
        const unsigned int _offset,
        const unsigned int _size,
        const void* _data,
        const bool _discard = false)
    {
        if (_discard) {
            destroy();
            create(m_size, NULL, m_flags);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _offset, _size, _data);
    }

    void destroy()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_id);
    }

    GLuint m_id;
    unsigned int m_size;
    unsigned short int m_flags;
};