#include <stdio.h>
#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "obj_parser.h"
#include "vao.h"

const unsigned int window_width{ 800 };
const unsigned int window_height{ 600 };

void frame_buffer_size_callback(GLFWwindow* window, const int width, const int height);
void process_input(GLFWwindow* window);

int main()
{
    Mesh m;
    ObjParser::parse("data/models/cube.obj", m);

    // TODO: next
    // GLuint vao = VAO::from_mesh(m);
    std::cout << "ok" << std::endl;
    return 0;








    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "openGLearn", NULL, NULL);
    if (window == NULL) {
        printf("Error creating window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    // load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    Mesh* box = new Mesh();
    World world(10);

    unsigned int camera;
    if (!world.create_entity(camera)) {
        return -1;
    }
    world.add_component(camera, ComponentType::Transform);

    std::vector<unsigned int> boxes(5);
    for (int i = 0; i < boxes.size(); ++i)
    {
        if (!world.create_entity(boxes[i])) {
            return -1;
        }
        world.add_components(
            boxes[i],
            { ComponentType::Transform, ComponentType::Mesh });

       Component* c = world.get_component(boxes[i], ComponentType::Mesh);
       c = box;
    }

    unsigned int shader = Shader::create(
        "data/shaders/testShader.vert",
        "data/shaders/testShader.frag");

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind our data from buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    GLuint texture1 = Texture::load("data/textures/wall.jpg");
    GLuint texture2 = Texture::load("data/textures/smiley.png");

    Shader::use(shader);
    Shader::set_int(shader, "texture1", 0);
    Shader::set_int(shader, "texture2", 1);

    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // glm::mat4 view = cam.get_as_view_matrix();

        Shader::use(shader);
        // Shader::set_mat4(shader, "view",  view);
        Shader::set_mat4(shader, "proj",  proj);
        Shader::set_float(shader, "blending", 0.5f);

        glBindVertexArray(vao);
        for (unsigned int i = 0; i < 10; ++i) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if (i % 2 == 0) {
                float angle = 20.0f * i;
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            Shader::set_mat4(shader, "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}