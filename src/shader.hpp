#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

struct Shader {
  Shader() : id(0) {}
  Shader(const char* vert_source, const char* frag_source);

  unsigned int id;
};
