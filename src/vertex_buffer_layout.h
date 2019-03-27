#pragma once

#include <vector>

#include "renderer.h"

struct VertexBufferElement
{
    unsigned int count;
    unsigned int type;
    unsigned int normalized;

    static unsigned int sizeof_gl_type(unsigned int type)
    {
        switch (type) {
            case GL_FLOAT         : return 4;
            case GL_UNSIGNED_INT  : return 4;
            case GL_UNSIGNED_BYTE : return 1;
            default: return 0;
        }
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
        : m_stride(0)
    {}

    template <typename T>
    void push(unsigned int count);

    template<>
    void push<float>(unsigned int count)
    {
        m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_stride += VertexBufferElement::sizeof_gl_type(GL_FLOAT);
    }

    template<>
    void push<unsigned int>(unsigned int count)
    {
        m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_stride += count * VertexBufferElement::sizeof_gl_type(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(unsigned int count)
    {
        m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_stride += count * VertexBufferElement::sizeof_gl_type(GL_UNSIGNED_BYTE);
    }

    inline unsigned int get_stride() const
    { return m_stride; }

    inline const std::vector<VertexBufferElement> get_elements() const
    { return m_elements; }

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
};