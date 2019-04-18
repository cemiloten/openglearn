#include "renderer.hpp"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer(unsigned int width, unsigned int height)
    : _width(width), _height(height) {}

void Renderer::render(const Scene* scene) {
  glClearColor(0.1f, 0.15f, 0.20f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const Camera& camera = scene->camera;

  glm::mat4 view = camera.getViewMatrix();
  glm::mat4 proj = glm::perspective(
      glm::radians(45.0f), _width / static_cast<float>(_height), 0.1f, 100.0f);
  glm::mat4 model(1.0f);

  glm::vec3 light_color(1.0f);
  glm::vec3 light_world_pos(scene->transforms[1].translation);


  for (size_t i = 0; i < scene->instances.size(); ++i) {
    const Instance& instance = scene->instances[i];

    const Mesh& mesh = scene->getMesh(instance);
    const Transform& transform = scene->getTransform(instance);
    const Material& material = scene->getMaterial(instance);

    glBindVertexArray(mesh.vao);
    model = glm::translate(model, transform.translation);
    model = glm::scale(model, transform.scale);

    const Shader& shader = scene->getShader(material);
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", proj);

    shader.setMaterialUniforms(material);
    shader.setVec3("light_color", light_color);
    shader.setVec3("light_world_pos", light_world_pos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
  }
}
