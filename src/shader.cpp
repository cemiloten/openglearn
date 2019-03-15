#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"
#include "fileutil.h"

unsigned int Shader::create(const char* vertPath, const char* fragPath)
{
    int success;
    char infoLog[512];
    const std::string vertSource = FileUtil::get_file_content(vertPath);
    const std::string fragSource = FileUtil::get_file_content(fragPath);

    // const char* vertSource =
    //     "#version 330 core\n"
    //     "layout (location = 0) in vec3 pos;\n"
    //     "layout (location = 1) in vec3 vertexColorIn;\n"
    //     "\n"
    //     "out vec3 vertexColor;\n"
    //     "\n"
    //     "void main() {\n"
    //         "gl_Position = vec4(pos, 1.0);\n"
    //         "vertexColor = vertexColorIn;\n"
    //     "}\n";

    // const char* fragSource =
    //     "#version 330 core\n"
    //     "out vec4 fragColor;\n"
    //     "in vec3 vertexColor;\n"
    //     "\n"
    //     "void main() {\n"
    //         "fragColor = vec4(vertexColor, 1.0);\n"
    //     "}\n";

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const GLchar* const*)&vertSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR: Vertex shader compilation failed\n%s\n", infoLog);
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const GLchar* const*)fragSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR: Fragment shader compilation failed\n%s\n", infoLog);
    }

    unsigned int shader_id;
    shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex);
    glAttachShader(shader_id, fragment);
    glLinkProgram(shader_id);
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_id, 512, NULL, infoLog);
        printf("ERROR: Shader program linking failed\n%s\n", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader_id;
}

// void Shader::SetBool(const std::string &name, const bool value) const {
//     glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
// }

// void Shader::SetInt(const std::string &name, const int value) const {
//     glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
// }

// void Shader::SetFloat(const std::string &name, const float value) const {
//     glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
// }
