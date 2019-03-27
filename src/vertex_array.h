#pragma once

#include "vertex_buffer.h"

#pragma once

#include "vertex_buffer_layout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;

private:
    unsigned int m_renderer_id;
};