#pragma once

#include "scene.hpp"
#include "shader.hpp"

class Renderer {
public:
  Renderer(unsigned int width, unsigned int height);
  void render(const Scene* scene);

private:
  unsigned int _width;
  unsigned int _height;
};
