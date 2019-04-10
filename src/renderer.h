#pragma once

#include "scene.h"
#include "shader.h"

class Renderer {
  public:
    void renderScene(const std::unique_ptr<Scene> scene);

  private:
    void draw(const Mesh& mesh, const Shader& shader);

};
