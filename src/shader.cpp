#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

#include "shader.h"

Shader::Shader(const char* vert_path, const char* frag_path) {
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

  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    printf("ERROR: Shader program linking failed\n%s\n", infoLog);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
