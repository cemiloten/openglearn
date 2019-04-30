#pragma once

#include <string>

#include "glad/glad.h"

struct ShaderType {
  enum Enum : unsigned int {
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
  };

  static inline std::string toString(Enum type) {
    switch (type) {
    case Vertex:
      return "Vertex";
    case Fragment:
      return "Fragment";
    default:
      return "Unknown";
    }
  }
};

struct Shader {
  unsigned int id;

  Shader(ShaderType::Enum type, const char* source_filename);
};
