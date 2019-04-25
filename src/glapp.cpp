#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "glapp.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


IGLApp::IGLApp(unsigned int width, unsigned int height) {
  glfwSetErrorCallback(IGLApp::onError);

  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    exit(1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
  const char* glsl_version = "#version 130";
#endif

  _window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
  assert(_window != nullptr && "Could not create GLFW window");
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1); // vsync

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD function pointers\n");
    exit(1);
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Keyboard controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Gamepad controls

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Disable mouse cursor (still enabled virtually)
  // glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // if (glfwRawMouseMotionSupported()) {
  //   printf("Raw mouse motion is supported\n");
  //   glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  // }

  // Register callbacks
  glfwSetWindowUserPointer(_window, this);
  glfwSetCursorPosCallback(_window, IGLApp::onCursorPos);
  glfwSetFramebufferSizeCallback(_window, IGLApp::onFrameBufferSize);

  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
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
