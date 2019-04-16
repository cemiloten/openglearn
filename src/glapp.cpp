#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "glapp.hpp"

IGLApp::IGLApp(unsigned int width, unsigned int height) {
  int major, minor, rev;
  glfwGetVersion(&major, &minor, &rev);
  printf("GLFW version: %d.%d.%d\n", major, minor, rev);
  glfwSetErrorCallback(IGLApp::onError);
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
  glfwSetFramebufferSizeCallback(_window, IGLApp::onFrameBufferSize);
}

IGLApp::~IGLApp() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void IGLApp::onCursorPos(float xpos, float ypos) {
  (void)xpos;
  (void)ypos;
}

void IGLApp::onFrameBufferSize(int width, int height) {
  glViewport(0, 0, width, height);
}

void IGLApp::onError(int error, const char* description) {
    fprintf(stderr, "Error %d, %s\n", error, description);
}

void IGLApp::onCursorPos(GLFWwindow* window, double xpos, double ypos) {
  IGLApp* app = static_cast<IGLApp*>(glfwGetWindowUserPointer(window));
  app->onCursorPos(static_cast<float>(xpos), static_cast<float>(ypos));
}

void IGLApp::onFrameBufferSize(GLFWwindow* window, int width, int height) {
  IGLApp* app = static_cast<IGLApp*>(glfwGetWindowUserPointer(window));
  app->onFrameBufferSize(width, height);
}
