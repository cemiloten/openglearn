#include <iostream>

#include "shader.hpp"
#include "utils.hpp"

Shader::Shader(const char* vert_path, const char* frag_path) {
  const char* vert_source = utils::fileContentsToString(vert_path).c_str();
  std::cout << vert_source << "\n";
  const char* frag_source = utils::fileContentsToString(frag_path).c_str();
  std::cout << frag_source << "\n";
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
