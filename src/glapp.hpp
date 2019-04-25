#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

class IGLApp {
protected:
  GLFWwindow* _window;

  IGLApp(unsigned int width, unsigned int height);
  ~IGLApp();
  IGLApp(const IGLApp&) = delete;
  void operator=(const IGLApp&) = delete;

  virtual void run() = 0;
  virtual void update(float delta_time) = 0;
  virtual void processInput(float delta_time) = 0;

  virtual void onCursorPos(float xpos, float ypos);
  virtual void onFrameBufferSize(int width, int height);

private:
  static void onError(int error, const char* description);
  static void onCursorPos(GLFWwindow* window, double xpos, double ypos);
  static void onFrameBufferSize(GLFWwindow* window, int width, int height);
};
