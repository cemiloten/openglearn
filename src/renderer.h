#pragma once

#include "scene.h"
#include "shader.h"

class Renderer {
public:
  Renderer(unsigned int width, unsigned int height);
  void render(const Scene* scene);

private:
  unsigned int _width;
  unsigned int _height;
};
