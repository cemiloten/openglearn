#pragma once

#include "scene.h"
#include "shader.h"

class Renderer {
public:
  void render(const Scene* scene);

private:
  // unsigned int _back_buffer;
  // unsigned int _back_buffer_width;
  // unsigned int _back_buffer_height;
};
