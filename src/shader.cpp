#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

#include "shader.h"

unsigned int Shader::create(const char* vert_path, const char* frag_path) {
    std::string vert_source_;
    std::string frag_source_;
    std::ifstream vert_shader_file;
    std::ifstream frag_shader_file;
    vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vert_shader_file.open(vert_path);
        frag_shader_file.open(frag_path);
        std::stringstream vert_shader_stream;
        std::stringstream frag_shader_stream;
        vert_shader_stream << vert_shader_file.rdbuf();
        frag_shader_stream << frag_shader_file.rdbuf();
        vert_shader_file.close();
        frag_shader_file.close();
        // convert stream into string
        vert_source_ = vert_shader_stream.str();
        frag_source_ = frag_shader_stream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR: Shader file not successfully read" << std::endl;
    }

    const char* vert_source = vert_source_.c_str();
    const char* frag_source = frag_source_.c_str();
    int success;
    char infoLog[512];

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vert_source, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR: Vertex shader compilation failed\n%s\n", infoLog);
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &frag_source, NULL);
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

void Shader::use(const unsigned int id) { glUseProgram(id); }

void Shader::set_bool(const unsigned int id, const std::string& param,
                      const bool value) {
    glUniform1i(glGetUniformLocation(id, param.c_str()), (int)value);
}

void Shader::set_int(const unsigned int id, const std::string& param,
                     const int value) {
    glUniform1i(glGetUniformLocation(id, param.c_str()), value);
}

void Shader::set_float(const unsigned int id, const std::string& param,
                       const float value) {
    glUniform1f(glGetUniformLocation(id, param.c_str()), value);
}

void Shader::set_vec2(const unsigned int id, const std::string& param,
                      const glm::vec2& value) {
    glUniform2fv(glGetUniformLocation(id, param.c_str()), 1, &value[0]);
}

void Shader::set_vec2(const unsigned int id, const std::string& param,
                      const float x, const float y) {
    glUniform2f(glGetUniformLocation(id, param.c_str()), x, y);
}

void Shader::set_vec3(const unsigned int id, const std::string& param,
                      const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(id, param.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const unsigned int id, const std::string& param,
                      const float x, const float y, const float z) {
    glUniform3f(glGetUniformLocation(id, param.c_str()), x, y, z);
}

void Shader::set_vec4(const unsigned int id, const std::string& param,
                      const glm::vec4& value) {
    glUniform4fv(glGetUniformLocation(id, param.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const unsigned int id, const std::string& param,
                      const float x, const float y, const float z,
                      const float w) {
    glUniform4f(glGetUniformLocation(id, param.c_str()), x, y, z, w);
}

void Shader::set_mat2(const unsigned int id, const std::string& param,
                      const glm::mat2& mat) {
    glUniformMatrix2fv(glGetUniformLocation(id, param.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
}

void Shader::set_mat3(const unsigned int id, const std::string& param,
                      const glm::mat3& mat) {
    glUniformMatrix3fv(glGetUniformLocation(id, param.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
}

void Shader::set_mat4(const unsigned int id, const std::string& param,
                      const glm::mat4& mat) {
    glUniformMatrix4fv(glGetUniformLocation(id, param.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
}
