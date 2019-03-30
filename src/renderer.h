#pragma once

#include "index_buffer.h"
#include "vertex_buffer.h"
#include "shader.h"
// #include "program.h"
#include "texture.h"

struct RendererContext
{
    IndexBuffer m_index_buffers[1024];
    VertexBuffer m_vertex_buffers[1024];
    // Shader m_shaders[1024];
    // Program m_programs[1024];
    // Texture m_textures[1024];

    void create_index_buffer(
        const IndexBufferHandle _handle,
        const unsigned int* _data,
        const unsigned int _size);

    void destroy_index_buffer(const IndexBufferHandle _handle);

    void create_vertex_buffer(
        const VertexBufferHandle _handle,
        const unsigned int* _data,
        const unsigned int _size,
        const VertexDeclHandle _declHandle);

    void destroy_vertex_buffer(const VertexBufferHandle _handle);
};
