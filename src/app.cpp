#include <memory>

#include "app.h"
#include "camera.h"
#include "mesh.h"
#include "obj_importer.h"

App::App(const char* name, unsigned int width, unsigned int height)
    : _name(name), _width(width), _height(height), _renderer(width, height) {

  if (!glfwInit()) {
    exit(1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  _window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
  if (_window == NULL) {
    printf("Error creating window\n");
    glfwTerminate();
    exit(2);
  }
  glfwMakeContextCurrent(_window);

  // load OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    exit(3);
  }

  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  MeshData mesh_data = readObjFile("data/models/triangle.obj");
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

    // for (unsigned int i = 0; i < 10; ++i) {
    //   glm::mat4 model = glm::mat4(1.0f);
    //   model = glm::translate(model, cubePositions[i]);
    //   if (i % 2 == 0) {
    //     float angle = 20.0f * i;
    //     model = glm::rotate(model, (float)glfwGetTime() *
    //     glm::radians(angle),
    //                         glm::vec3(1.0f, 0.3f, 0.5f));
    //   }
    //   Shader::set_mat4(shader, "model", model);
    //   glDrawArrays(GL_TRIANGLES, 0, 36);
    // }
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
  return false;
}

int App::shutdown() {
  glfwTerminate();
  return 0;
}

void App::processInput() {
  if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
  }
  if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
  }
  if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
  }
  if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
  }
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(_window, true);
  }
}