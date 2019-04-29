#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

class IApp {
public:
  void run();

protected:
  GLFWwindow* _window;
  unsigned int _width;
  unsigned int _height;
  float _last_time;
  float _delta_time;

  IApp(unsigned int w, unsigned int h);
  ~IApp();
  IApp(const IApp&) = delete;
  void operator=(const IApp&) = delete;

  virtual void onStart() = 0;
  virtual void onUpdate(float delta_time) = 0;
  virtual void processInput() = 0;

  virtual void onCursorPos(float xpos, float ypos);
  virtual void onFrameBufferSize(int width, int height);

private:
  void update();

  static void onError(int error, const char* description);
  static void onCursorPos(GLFWwindow* window, double xpos, double ypos);
  static void onFrameBufferSize(GLFWwindow* window, int width, int height);
};
