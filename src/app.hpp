#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "scene.hpp"
#include "renderer.hpp"

class App {
public:
  App(unsigned int width, unsigned int height);
  bool update();
  int shutdown();

  void onCursorPos(float x, float y);

private:
  GLFWwindow* _window;
  Scene* _scene;
  Renderer _renderer;

  float _last_mouse_pos_x;
  float _last_mouse_pos_y;

  void processInput();

  static void onCursorPos(GLFWwindow* window, double x, double y);
};
