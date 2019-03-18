#include <stdio.h>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "shader.h"

const unsigned int window_width{ 800 };
const unsigned int window_height{ 600 };
float blending{ 0.0f };

void frame_buffer_size_callback(GLFWwindow* window, const int width, const int height);
void process_input(GLFWwindow* window);

int main()
{
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
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "openGLearn", NULL, NULL);
    if (window == NULL) {
        printf("Error creating window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    // glad: load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    unsigned int shader = Shader::create("src/shaders/testShader.vert",
                                         "src/shaders/testShader.frag");

    float vertices[] {
        // positions         // colors            // uv coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    unsigned int indices[6] {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // bind vertex array object
    glBindVertexArray(vao);
    // copy our vertices array in a vertex buffer for opengl to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set the vertex attributes pointers
    // vertex data layout: [pos.x, pos.y, pos.z, col.r, col.g, col.b, uv.x, uv.y]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // texture stuff
    unsigned int texture1;
    unsigned int texture2;
    const char* tex_path1 = "data/textures/wall.jpg";
    const char* tex_path2 = "data/textures/smiley.png";
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int tex_width, tex_height, normal_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* tex_data = stbi_load(tex_path1, &tex_width, &tex_height, &normal_channels, 0);
    if (tex_data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture1%s\n", tex_path1);
    }

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex_data = stbi_load(tex_path2, &tex_width, &tex_height, &normal_channels, 0);
    if (tex_data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture2%s\n", tex_path2);
    }

    stbi_image_free(tex_data);


    // unbind our data from buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE or GL_FILL

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        int blending_location = glGetUniformLocation(shader, "blending");
        Shader::use(shader);
        glUniform1f(blending_location, blending);
        Shader::set_int(shader, "texture1", 0);
        Shader::set_int(shader, "texture2", 1);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
    return 0;
}

void frame_buffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height); // Match new dimensions
}

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        // blending
        blending += 0.01f;
        if (blending > 1.0f) {
            blending = 1.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        blending -= 0.01f;   // blending
        if (blending < 0.0f) {
            blending = 0.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}