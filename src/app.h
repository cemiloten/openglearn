#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "mesh.h"
#include "shader.h"
#include "scene.h"
#include "renderer.h"

struct App {
  public:
    App(const char* name, unsigned int width, unsigned int height);
    bool update();
    int shutdown();

  private:
    const char* _name;
    unsigned int _width;
    unsigned int _height;
    GLFWwindow* _window;

    std::unique_ptr<Scene> _scene;
    Renderer _renderer;
};