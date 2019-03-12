#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const unsigned int windowWidth  = 800;
const unsigned int windowHeight = 600;

int main()
{
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GL_MAJOR_VERSION, 3);
    glfwWindowHint(GL_MINOR_VERSION, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Window
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "openGLearn", glfwGetPrimaryMonitor(), NULL);
    if (window == NULL) {
        printf("Error creating window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    printf("hellopengl\n");
    return 0;
}