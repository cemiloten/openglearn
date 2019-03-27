#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
};
