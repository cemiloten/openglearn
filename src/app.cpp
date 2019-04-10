#include <memory>

#include "app.h"
#include "obj_importer.h"

App::App(const char* name, unsigned int width, unsigned int height)
    : _name(name), _width(width), _height(height) {

    if (!glfwInit()) {
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = glfwCreateWindow(_width, _height, "openGLearn", NULL, NULL);
    if (_window == NULL) {
        printf("Error creating window\n");
        glfwTerminate();
        exit(2);
    }
    glfwMakeContextCurrent(_window);
    // glfwSetFramebufferSizeCallback(_window, frame_buffer_size_callback);

    // load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        exit(3);
    }

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    MeshData mesh_data = readObjFile("data/models/cube.obj");
    Mesh mesh(mesh_data);
    Shader shader("data/shaders/test.vert", "data/shaders/test.frag");

    // _scene = std::make_unique<Scene>();
    // _scene->_meshes.push_back(mesh);

    // _renderer.
    // _scene->_shaders.push_back(shader);
}

bool App::update() {
    while (!glfwWindowShouldClose(_window)) {
        // process_input(_window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // _shader.use();

        // glBindVertexArray(_mesh.vao);
        // glDrawElements(GL_TRIANGLES, _mesh.vertex_count, GL_UNSIGNED_INT,
        //                (void*)0);





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

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    return false;
}

int App::shutdown() {
    glfwTerminate();
    return 0;
}