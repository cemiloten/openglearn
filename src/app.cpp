#include <memory>

#include "app.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "obj_importer.hpp"
#include "shader.hpp"

App::App(unsigned int width, unsigned int height)
    : _renderer(width, height), _last_mouse_pos_x(0.5f * width),
      _last_mouse_pos_y(0.5f * height) {

  if (!glfwInit()) {
    exit(1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  _window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
  assert(_window != NULL && "Could not create GLFW window");

  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, this);

  // Callbacks
  glfwSetCursorPosCallback(_window, onCursorPos);

  // load OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    exit(3);
  }

  glfwSetCursorPos(_window, _last_mouse_pos_x, _last_mouse_pos_y);

  // glfwSwapInterval(1);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);

  // // clang-format off
  // std::vector<Vertex> vertices{
  //     { -0.5f, 0.0f, 0.5f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f }, // bottom left
  //     { 0.5f,  0.0f, 0.5f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f }, // bottom right
  //     { -0.5f, 0.0f, -0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f }, // top left
  //     { 0.5f,  0.0f, -0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f } // top right
  // }; // clang-format on

  // std::vector<unsigned int> indices{0, 1, 3, 3, 2, 0};

  // Initalize data
  // MeshData mesh_data(vertices, indices);
  MeshData mesh_data = readObjFile("data/models/cube.obj");
  _scene = new Scene;
  _scene->mesh = Mesh(mesh_data);
  _scene->shader = Shader("data/shaders/test.vert", "data/shaders/test.frag");
  _scene->camera = Camera();
}

bool App::update() {
  while (!glfwWindowShouldClose(_window)) {
    processInput();

    _renderer.render(_scene);

    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
  return false;
}

int App::shutdown() {
  glfwTerminate();
  return 0;
}

void App::processInput() {
  float speed = 0.1f;
  Camera& cam = _scene->camera;

  if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS ||
      glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
    cam.position -= cam.right * speed;
  }

  if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
      glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
    cam.position += cam.right * speed;
  }

  if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS ||
      glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
    cam.position += cam.front * speed;
  }

  if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS ||
      glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
    cam.position -= cam.front * speed;
  }

  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(_window, true);
  }
}

void App::onCursorPos(float x, float y) {
  float dx = x - _last_mouse_pos_x;
  float dy = _last_mouse_pos_y - y;
  _last_mouse_pos_x = x;
  _last_mouse_pos_y = y;

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

void App::onCursorPos(GLFWwindow* window, double x, double y) {
  App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
  app->onCursorPos(static_cast<float>(x), static_cast<float>(y));
}
