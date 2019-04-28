#include <cstdlib>
#include <iostream>

#include "app.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "json.hpp"
#include "renderer.hpp"

// TODO:
// read scene file
// save image
// from real time view, launch ray tracing process

class App : public IApp {
public:
  App(const char* launch_file_path) : IApp(launch_file_path) {

    _last_mouse_pos_x = 0.5f * _width;
    _last_mouse_pos_y = 0.5f * _height;
    glfwSetCursorPos(_window, _last_mouse_pos_x, _last_mouse_pos_y);
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

    renderer::draw(_scene);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);
  }

  virtual void processInput(float delta_time) override {
    float speed = 8.0f;
    Camera& cam = _scene->camera;

    // Left
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
      cam.position -= cam.right * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      _scene->transforms[1].translation -=
          glm::vec3(1.0f, 0.0f, 0.0f) * speed * delta_time;
    }

    // Right
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
      cam.position += cam.right * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      _scene->transforms[1].translation +=
          glm::vec3(1.0f, 0.0f, 0.0f) * speed * delta_time;
    }

    // Up
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
      cam.position += cam.front * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
      _scene->transforms[1].translation -=
          glm::vec3(0.0f, 0.0f, 1.0f) * speed * delta_time;
    }

    // Down
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
      cam.position -= cam.front * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      _scene->transforms[1].translation +=
          glm::vec3(0.0f, 0.0f, 1.0f) * speed * delta_time;
    }

    if (glfwGetKey(_window, GLFW_KEY_ENTER) == GLFW_PRESS) {
      _scene->transforms[1].translation +=
          glm::vec3(0.0f, 1.0f, 0.0f) * speed * delta_time;
    }

    if (glfwGetKey(_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
      _scene->transforms[1].translation -=
          glm::vec3(0.0f, 1.0f, 0.0f) * speed * delta_time;
    }

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
    float dx = xpos - _last_mouse_pos_x;
    float dy = _last_mouse_pos_y - ypos;
    _last_mouse_pos_x = xpos;
    _last_mouse_pos_y = ypos;

    float mouse_sensitivity = 0.35f;
    Camera& cam = _scene->camera;

    cam.yaw -= dx * mouse_sensitivity;
    cam.pitch += dy * mouse_sensitivity;

    if (cam.pitch > 89.0f) {
      cam.pitch = 89.0f;
    }
    if (cam.pitch < -89.0f) {
      cam.pitch = -89.0f;
    }

    cam.updateVectors();
  }

private:
  float _last_mouse_pos_x;
  float _last_mouse_pos_y;
};

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: [launch_file.json]");
    return 1;
  }

  const char* launch_filepath = argv[1];
  App app(launch_filepath);
  app.start();

  return 0;
}
