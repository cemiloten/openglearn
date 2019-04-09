#include <cmath>
#include <cstdio>
#include <iostream>

#include "mesh.h"
#include "obj_importer.h"
#include "ogl.h"
#include "shader.h"
#include "texture.h"
#include "world.h"

void frame_buffer_size_callback(GLFWwindow* window, const int width,
                                const int height);
void process_input(GLFWwindow* window);

struct App {
    App(const char* _name, const char* _description)
        : m_name(_name), m_description(_description) {}

    void initialize(const int _argc, const char* const* _argv,
                    const unsigned int _width, const unsigned int _height) {
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

        m_window =
            glfwCreateWindow(m_width, m_height, "openGLearn", NULL, NULL);
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

        m_mesh = readObjFile("data/models/cube.obj");
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        // create vertex buffer
        // create index buffer

        // TODO:
        // fill buffers to draw mesh
    }

    bool update() {
        while (!glfwWindowShouldClose(m_window)) {
            process_input(m_window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            //         model = glm::rotate(model, (float)glfwGetTime() *
            //         glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //     }
            //     Shader::set_mat4(shader, "model", model);
            //     glDrawArrays(GL_TRIANGLES, 0, 36);
            // }
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
        return false;
    }

    int shutdown() {
        // glDeleteVertexArrays(1, &cube);
        // glDeleteBuffers(1, &vbo);
        // glDeleteBuffers(1, &ebo);
        glfwTerminate();
        std::cout << "shutting down..." << std::endl;
        return 0;
    }

    inline const char* get_name() const { return m_name; }
    inline const char* get_description() const { return m_description; }

   private:
    const char* m_name;
    const char* m_description;
    unsigned int m_width;
    unsigned int m_height;
    GLFWwindow* m_window;
    Mesh m_mesh;
};

int main(int argc, char* argv[]) {
    App app("OpenGLearn", "A simple sandbox app for experimenting with OpenGL");
    app.initialize(argc, argv, 800, 600);

    while (app.update()) {
    }

    app.shutdown();
    return 0;
}

void frame_buffer_size_callback(GLFWwindow* window, const int width,
                                const int height) {
    glViewport(0, 0, width, height);  // Match new dimensions
}

void process_input(GLFWwindow* window) {
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