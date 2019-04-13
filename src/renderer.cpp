#include "renderer.hpp"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer(unsigned int width, unsigned int height)
    : _width(width), _height(height) {}

void Renderer::render(const Scene* scene) {
  glViewport(0, 0, _width, _height);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const Shader& shader = scene->shader;
  const Camera& camera = scene->camera;

  glm::mat4 view = glm::translate(camera.getViewMatrix(), glm::vec3(0.0f, 0.0f, 3.0f));
  int view_loc = glGetUniformLocation(shader.id, "view");
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 proj(1.0f);
  proj = glm::perspective(glm::radians(45.0f),
                          _width / static_cast<float>(_height), 0.1f, 100.0f);
  int proj_loc = glGetUniformLocation(shader.id, "proj");
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

  glm::mat4 model(1.0f);

  for (size_t i = 0; i < scene->instances.size(); ++i) {
    const Instance& instance = scene->instances[i];
    const Mesh& mesh = scene->meshes[instance.mesh.id];
    const Transform& transform = scene->transforms[instance.transform.id];

    glUseProgram(scene->shader.id);

    glBindVertexArray(mesh.vao);
    model = glm::translate(model, transform.translation);
    int model_loc = glGetUniformLocation(shader.id, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
  }


}
