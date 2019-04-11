#include "renderer.h"
#include "glad/glad.h"

void Renderer::render(const Scene* scene) {
  //   glBindFramebuffer(GL_FRAMEBUFFER, _back_buffer);
  //   glViewport(0, 0, _back_buffer_width, _back_buffer_height);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //   glClearDepth(0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBindVertexArray(scene->mesh.vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene->mesh.ebo);
  glUseProgram(scene->shader.id);
  glDrawElements(GL_TRIANGLES, scene->mesh.vertex_count, GL_UNSIGNED_INT, 0);

  //   const Camera& cam = scene->camera;
  //   for (const auto& instance : scene->instances) {
  //     const Mesh& mesh = scene->meshes[instance.mesh_id];
  //     draw(mesh, scene->shader);
  //   }
}
