#include <iostream>

#include "app.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "json.hpp"
#include "renderer.hpp"
#include "gltf_loader.hpp"

// TODO:
// read gltf file
// load gltf file into tinygltf::Model
// if needed, translate to own scene graph
// display gltf scene
// scene navigation (remove fps navigation)
// save buffer to image file
// from real time view, launch ray tracing process

// NOTES:
// we can support only one shader because no need for effects and things like
// that.

class App : public IApp {
public:
  tinygltf::Model _model;

  App(unsigned int w, unsigned int h, const char* gltf_path) : IApp(w, h) {
    bool res = gltf_loader::loadModel(_model, gltf_path);
    assert(res && "Error, could not load glTF file");
  }

  virtual void onStart() override {}

  virtual void onUpdate(float dt) override {
    (void)dt;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
    ImGui::Render();

    glClearColor(0.1f, 0.15f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer::drawModel(_model);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);
  }

  virtual void processInput() override {
    // View mode
    if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    // Quit
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(_window, true);
    }
  }

  virtual void onCursorPos(float xpos, float ypos) override {
    (void)xpos;
    (void)ypos;
  }
};

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: renderer config_file.json" << std::endl;
    return 1;
  }

  const char* config_filepath = argv[1];
  App app(800, 800, config_filepath);
  app.run();

  return 0;
}
