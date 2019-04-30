#pragma once

#include <map>

#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "shader.hpp"

struct ShaderProgram {
  unsigned int id;
  // std::map<std::string, int> attributes;
  // std::map<std::string, int> uniforms;

  ShaderProgram(const char* vert_filename, const char* frag_filename);
  ShaderProgram(Shader vertex, Shader fragment);

  inline void use() const { glUseProgram(id); }

  inline void setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
  }

  inline void setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
  }

  inline void setVec3(const std::string& name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
  }

  inline void setMat4(const std::string& name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
  }
};
