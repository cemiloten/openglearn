#pragma once

#include "index_buffer.h"
#include "ogl.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "vertex_buffer_view.h"

// #include "program.h"
#include "texture.h"

struct RendererContext {
    VertexBuffer vertexBuffers[1024];
    IndexBuffer indexBuffers[1024];
    // Shader m_shaders[1024];
    // Program m_programs[1024];

    VertexBufferHandle createVertexBuffer(const void* data,
                                          const unsigned int size,
                                          const VertexBufferView view);

    // IndexBufferHandle createIndexBuffer(const IndexBufferHandle handle,
    //                                     const Memory memory);

    void destroyVertexBuffer(const VertexBufferHandle handle);

    // void destroyIndexBuffer(const IndexBufferHandle handle);
};
