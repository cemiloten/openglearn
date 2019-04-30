#include <iostream>

#include "shader.hpp"
#include "utils.hpp"

Shader::Shader(ShaderType::Enum type, const char* source_filename) {
  const char* source = utils::fileToString(source_filename).c_str();

  int success = 0;
  char info_log[512];

  id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(id, 512, NULL, info_log);
    std::cerr << "ERROR: " << ShaderType::toString(type)
              << " shader compilation failed\n"
              << info_log << std::endl;
  }
}
