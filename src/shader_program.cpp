#include <iostream>

#include "shader_program.hpp"

ShaderProgram::ShaderProgram(const char* vert_filename,
                             const char* frag_filename)
    : ShaderProgram(Shader(ShaderType::Enum::Vertex, vert_filename),
                    Shader(ShaderType::Enum::Fragment, frag_filename)) {}

ShaderProgram::ShaderProgram(Shader vertex, Shader fragment) {
  id = glCreateProgram();
  glAttachShader(id, vertex.id);
  glAttachShader(id, fragment.id);
  glLinkProgram(id);

  int success = 0;
  char info_log[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, info_log);
    std::cerr << "ERROR: Shader program linking failed\n"
              << info_log << std::endl;
  }

  glDeleteShader(vertex.id);
  glDeleteShader(fragment.id);
}
