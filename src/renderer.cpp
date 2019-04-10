#include "glad/glad.h"
#include "renderer.h"

void Renderer::renderScene(const std::unique_ptr<Scene> scene) {
    const Camera& cam = scene->camera;

    for (const auto& instance : scene->instances) {

    }
    // draw each instance
}

void Renderer::draw(const Mesh& mesh, const Shader& shader) {
    glBindVertexArray(mesh.vao);
    // get instance's mesh and transform
    // bind
    // draw
    // unbind
}