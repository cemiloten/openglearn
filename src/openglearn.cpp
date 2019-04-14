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

    MeshData ground = readObjFile("data/models/quad.obj");
    _scene->meshes.push_back(Mesh(ground));

    MeshData mesh_data = readObjFile(obj_path);
    _scene->meshes.push_back(Mesh(mesh_data));

    _scene->transforms.resize(10);
    _scene->transforms[0].scale = glm::vec3(10.0f, 10.0f, 10.0f); // Ground

    _scene->transforms[1].translation = glm::vec3(1.0f, 0.0f, 0.0f);
    _scene->transforms[2].translation = glm::vec3(-1.0f, 0.0f, 0.0f);
    _scene->transforms[3].translation = glm::vec3(0.0f, -1.0f, 0.3f);
    _scene->transforms[4].translation = glm::vec3(0.0f, 1.0f, 0.0f);
    _scene->transforms[5].translation = glm::vec3(-2.7f, 0.0f, -0.5f);
    _scene->transforms[6].translation = glm::vec3(2.3f, -0.0f, -0.5f);
    _scene->transforms[7].translation = glm::vec3(0.5f, 0.0f, -2.5f);
    _scene->transforms[8].translation = glm::vec3(0.5f, 0.0f, 1.5f);
    _scene->transforms[9].translation = glm::vec3(-0.3f, 3.0f, -0.5f);

    _scene->instances.reserve(10);
    _scene->instances.push_back(Instance(0, 0));

    for (unsigned short int i = 1; i < 10; ++i) {
      _scene->instances.push_back(Instance(1, i));
      Transform& trs = _scene->transforms[_scene->instances[i].transform.id];
      printf("scale is : %f, %f, %f\n", trs.scale.x, trs.scale.y, trs.scale.z);
    }

    _scene->shader = Shader("data/shaders/test.vert", "data/shaders/test.frag");
    _scene->camera = Camera();
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
    float speed = 1.0f;
    Camera& cam = _scene->camera;

    if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS ||
        glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
      cam.position -= cam.right * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
        glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
      cam.position += cam.right * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS ||
        glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
      cam.position += cam.front * speed * delta_time;
    }
    if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS ||
        glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
      cam.position -= cam.front * speed * delta_time;
    }
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

    cam.yaw += dx * mouse_sensitivity;
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
  if (argc == 2) {
    App app(1280, 720, argv[1]);
    app.run();
  } else if (argc == 4) {
    unsigned int w(atoi(argv[2]));
    unsigned int h(atoi(argv[3]));
    App app(w, h, argv[1]);
    app.run();
  } else {
    printf("Usage: obj file path || obj file path, width, height\n");
    return 1;
  }
  return 0;
}
