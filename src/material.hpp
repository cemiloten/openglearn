#pragma once

#include "glm/vec3.hpp"

struct Material {
  unsigned int shader_id;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  Material(unsigned int _shader_id)
      : shader_id(_shader_id), ambient(0.0f), diffuse(0.5f), specular(0.5f) {}

  Material(unsigned int _shader_id, glm::vec3 _ambient, glm::vec3 _diffuse,
           glm::vec3 _specular)
      : shader_id(_shader_id), ambient(_ambient), diffuse(_diffuse),
        specular(_specular) {}
};