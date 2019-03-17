#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>

#include "shader.h"

const unsigned int windowWidth{ 800 };
const unsigned int windowHeight{ 600 };

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height);
void processInput(GLFWwindow* window);

// TODO: reading from file gives weird value
// need to do C style because that's what gl wants in glShaderSource
int main() {
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Window
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "openGLearn", NULL, NULL);
    if (window == NULL) {
        printf("Error creating window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // glad: load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    unsigned int shader = Shader::create(
        "src/shaders/testShader.vert",
        "src/shaders/testShader.frag");

    float vertices[] {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    // unsigned int indices[6] {
    //     0, 1, 3,
    //     1, 2, 3
    // };

    unsigned int vao;
    glGenVertexArrays(1, &vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);

    // bind vertex array object
    glBindVertexArray(vao);
    // copy our vertices array in a vertex buffer for opengl to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set the vertex attributes pointers
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind our data from buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE or GL_FILL

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        Shader::use(shader);
        Shader::set_float(shader, "h_offset", 0.4f);
        // testShader.setFloat("ourColor", 1.0f);

        // float timeValue = (float)glfwGetTime();
        // float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    // Match new dimensions
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}