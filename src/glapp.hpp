#pragma once

#include <cassert>
#include <cstdio>

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

class IGLApp {
protected:
  IGLApp(unsigned int width, unsigned int height) {
    if (!glfwInit()) {
      printf("Failed to initialize GLFW\n");
      exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
    assert(_window != nullptr && "Could not create GLFW window");
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      printf("Failed to initialize GLAD function pointers\n");
      exit(1);
    }

    glfwSetWindowUserPointer(_window, this);
    glfwSetCursorPosCallback(_window, IGLApp::onCursorPos);
  }

  ~IGLApp() {
    glfwDestroyWindow(_window);
    glfwTerminate();
  }

  IGLApp(const IGLApp&) = delete;
  void operator=(const IGLApp&) = delete;

  virtual void run() = 0;
  virtual void update() = 0;
  virtual void processInput() = 0;

  virtual void onCursorPos(float xpos, float ypos) = 0;

  GLFWwindow* _window;

private:
  static void onCursorPos(GLFWwindow* window, double xpos, double ypos) {
    IGLApp* app = static_cast<IGLApp*>(glfwGetWindowUserPointer(window));
    app->onCursorPos(static_cast<float>(xpos), static_cast<float>(ypos));
  }
};
