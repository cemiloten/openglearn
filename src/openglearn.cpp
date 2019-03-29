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
#include "app.h"

struct App
{
    App(const char* _name, const char* _description)
        : m_name(_name), m_description(_description)
    {}

    void initialize(
        const int _argc,
        const char* const* _argv,
        const unsigned int _width,
        const unsigned int _height)
    {
        m_width = _width;
        m_height = _height;

        // TODO: initialize vertex data etc.
        if (!glfwInit()) {
            exit(1);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_window = glfwCreateWindow(m_width, m_height, "openGLearn", NULL, NULL);
        if (m_window == NULL) {
            printf("Error creating window\n");
            glfwTerminate();
            exit(2);
        }
        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);

        // load OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            printf("Failed to initialize GLAD\n");
            exit(3);
        }

        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    int shutdown()
    {
        // glDeleteVertexArrays(1, &cube);
        // glDeleteBuffers(1, &vbo);
        // glDeleteBuffers(1, &ebo);
        // glfwTerminate();
    }

    bool update()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            process_input(m_window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, texture1);
            // glActiveTexture(GL_TEXTURE1);
            // glBindTexture(GL_TEXTURE_2D, texture2);

            // // glm::mat4 view = cam.get_as_view_matrix();

            // Shader::use(shader);
            // // Shader::set_mat4(shader, "view",  view);
            // Shader::set_mat4(shader, "proj",  proj);
            // Shader::set_float(shader, "blending", 0.5f);

            // VAO::bind(cube);
            // VAO::draw(cube, *box);

            // for (unsigned int i = 0; i < 10; ++i) {
            //     glm::mat4 model = glm::mat4(1.0f);
            //     model = glm::translate(model, cubePositions[i]);
            //     if (i % 2 == 0) {
            //         float angle = 20.0f * i;
            //         model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //     }
            //     Shader::set_mat4(shader, "model", model);
            //     glDrawArrays(GL_TRIANGLES, 0, 36);
            // }
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
        // process events
        // draw stuff
        return false;
    }

    const char* get_name() const { return m_name; }
    const char* get_description() const { return m_description; }

private:
    const char* m_name;
    const char* m_description;
    unsigned int m_width;
    unsigned int m_height;
    GLFWwindow* m_window;
};

void frame_buffer_size_callback(GLFWwindow* window, const int width, const int height);
void process_input(GLFWwindow* window);

int main()
{

    // unsigned int camera;
    // if (!world.create_entity(camera)) {
    //     return -1;
    // }
    // world.add_component(camera, ComponentType::Transform);

    // std::vector<unsigned int> boxes(5);
    // for (int i = 0; i < boxes.size(); ++i)
    // {
    //     if (!world.create_entity(boxes[i])) {
    //         return -1;
    //     }
    //     world.add_components(
    //         boxes[i],
    //         { ComponentType::Transform, ComponentType::Mesh });

    //    IComponent* c = world.get_component(boxes[i], ComponentType::Mesh);
    //    c = box;
    // }

    // unsigned int shader = Shader::create(
    //     "data/shaders/testShader.vert",
    //     "data/shaders/testShader.frag");

    // GLuint texture1 = Texture::load("data/textures/wall.jpg");
    // GLuint texture2 = Texture::load("data/textures/smiley.png");

    // Shader::use(shader);
    // Shader::set_int(shader, "texture1", 0);
    // Shader::set_int(shader, "texture2", 1);

    // glm::mat4 proj = glm::mat4(1.0f);
    // proj = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

    // GLuint cube = VAO::from_mesh(*box, VAO::DrawMode::Static);
    // return 0;
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