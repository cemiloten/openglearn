#pragma once

#include "scene.h"
#include "shader.h"

class Renderer {
  public:
    void render(std::unique_ptr<Scene> scene);

  private:
};
