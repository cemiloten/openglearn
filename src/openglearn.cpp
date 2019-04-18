#include <cstdlib>

#include "glapp.hpp"
#include "obj_importer.hpp"
#include "renderer.hpp"
#include "scene.hpp"

class App : IGLApp {
public:
  App(unsigned int width, unsigned int height, const char* obj_path)
      : IGLApp(width, height), _renderer(width, height),
        _last_mouse_pos_x(0.5f * width), _last_mouse_pos_y(0.5f * height) {

    glfwSetCursorPos(_window, _last_mouse_pos_x, _last_mouse_pos_y);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    // Initalize data
    _scene = new Scene;

    _scene->camera = Camera();
    _scene->camera.position += glm::vec3(0.0f, 2.0f, 2.0f);
    _scene->camera.pitch -= 45.0f;

    MeshData mesh_data = readObjFile(obj_path);
    _scene->meshes.push_back(Mesh(mesh_data));

    _scene->shaders.push_back(
        Shader("data/shaders/phong.vert", "data/shaders/phong.frag"));
    _scene->shaders.push_back(
        Shader("data/shaders/light.vert", "data/shaders/light.frag"));

    _scene->transforms.resize(2);

    // object
    _scene->materials.push_back(Material(0, glm::vec3(1.0f, 0.5f, 0.31f),
                                         glm::vec3(1.0f, 0.5f, 0.31f),
                                         glm::vec3(0.5f, 0.5f, 0.5f), 32.0f));
    _scene->instances.push_back(Instance(0, 0, 0));

    // light
    _scene->transforms[1].translation += glm::vec3(1.3f, 1.3f, -1.3f);
    _scene->transforms[1].scale *= 0.3f;
    _scene->materials.push_back(Material(1));
    _scene->instances.push_back(Instance(0, 1, 1));
  }

  ~App() { delete _scene; }

  virtual void run() override {
    while (!glfwWindowShouldClose(_window)) {
      float current_time = static_cast<float>(glfwGetTime());
      delta_time = current_time - last_time;
      update();
      last_time = current_time;
    }
  }

private:
  virtual void update() override {
    processInput();
    _renderer.render(_scene);
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }

  virtual void processInput() override {
    float speed = 4.0f;
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

    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      printf("debug\n");
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
  Scene* _scene;
  Renderer _renderer;

  float delta_time;
  float last_time;
  float _last_mouse_pos_x;
  float _last_mouse_pos_y;
};

int main(int argc, const char* argv[]) {
  unsigned int w = 640;
  unsigned int h = 480;

  if (argc == 1) {
    App app(w, h, "data/models/cube.obj");
    app.run();
  } else if (argc == 2) {
    App app(w, h, argv[1]);
    app.run();
  } else if (argc == 4) {
    w = atoi(argv[2]);
    h = atoi(argv[3]);
    App app(w, h, argv[1]);
    app.run();
  } else {
    printf("Usage: obj file path || obj file path, width, height\n");
    return 1;
  }
  return 0;
}
