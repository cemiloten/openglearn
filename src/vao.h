#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mesh.h"

namespace VAO
{

enum class DrawMode : unsigned int
{
    Static,
    Stream,
    Dynamic
};

int to_gl_draw_mode(DrawMode mode)
{
    switch (mode) {
        case DrawMode::Static  : return GL_STATIC_DRAW;
        case DrawMode::Stream  : return GL_STREAM_DRAW;
        case DrawMode::Dynamic : return GL_DYNAMIC_DRAW;
        default: return 0;
    }
}

GLuint from_mesh(const Mesh& mesh, DrawMode draw_mode = DrawMode::Static)
{
    int gl_draw_mode = to_gl_draw_mode(draw_mode);
    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    GLuint vertices;
    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices), &mesh.vertices[0], gl_draw_mode);

    GLuint texcoords;
    glGenBuffers(1, &texcoords);
    glBindBuffer(GL_ARRAY_BUFFER, texcoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.texcoords), &mesh.texcoords[0], gl_draw_mode);

    GLuint normals;
    glGenBuffers(1, &normals);
    glBindBuffer(GL_ARRAY_BUFFER, normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.normals), &mesh.normals[0], gl_draw_mode);

}

}