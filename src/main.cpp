#include "app.h"

// void frame_buffer_size_callback(GLFWwindow* window, const int width,
//                                 const int height);
// void process_input(GLFWwindow* window);

int main() {
    App app("OpenGLearn", 800, 600);
    while (app.update()) {}
    app.shutdown();
    return 0;
}

// void frame_buffer_size_callback(GLFWwindow* window, const int width,
//                                 const int height) {
//     (void)window;
//     glViewport(0, 0, width, height); // Match new dimensions
// }

// void process_input(GLFWwindow* window) {
//     if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
//     }
//     if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
//     }
//     if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
//     }
//     if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
//     }
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//         glfwSetWindowShouldClose(window, true);
//     }
// }
