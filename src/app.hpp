#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "scene.hpp"

class IApp {
public:
  void start();

protected:
  unsigned int _width;
  unsigned int _height;
  GLFWwindow* _window;
  Scene* _scene;

  float _last_time;
  float _delta_time;

  IApp(const char* launch_file_path);
  ~IApp();
  IApp(const IApp&) = delete;
  void operator=(const IApp&) = delete;

  virtual void onStart() = 0;
  virtual void onUpdate(float delta_time) = 0;
  virtual void processInput(float delta_time) = 0;

  virtual void onCursorPos(float xpos, float ypos);
  virtual void onFrameBufferSize(int width, int height);

private:
  void update();

  static void onError(int error, const char* description);
  static void onCursorPos(GLFWwindow* window, double xpos, double ypos);
  static void onFrameBufferSize(GLFWwindow* window, int width, int height);
};
