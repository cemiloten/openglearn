#include "app.h"

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
