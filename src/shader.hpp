#pragma once

#include <string>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "material.hpp"


struct Shader {
  unsigned int id;

  Shader() : id(0) {}
  Shader(const char* vert_source, const char* frag_source);

  inline void use() const { glUseProgram(id); }

  inline void setVec3(const std::string& name, glm::vec3 value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
  }

  inline void setMat4(const std::string& name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
  }

  inline void setMaterialUniforms(const Material& material) const {
    setVec3("ambient", material.ambient);
    setVec3("diffuse", material.diffuse);
    setVec3("specular", material.specular);
  }
};
