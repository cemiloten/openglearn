#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "scene.h"
#include "renderer.h"

class App {
public:
  App(const char* name, unsigned int width, unsigned int height);
  bool update();
  int shutdown();
  void processInput();

private:
  const char* _name;
  unsigned int _width;
  unsigned int _height;
  GLFWwindow* _window;

  Scene* _scene;
  Renderer _renderer;
};