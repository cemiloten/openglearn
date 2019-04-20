#pragma once

#include "glm/vec3.hpp"
#include "texture.hpp"

struct Material {
  size_t shader_id;
  size_t diffuse_id;

  glm::vec3 specular;
  float shininess;

  Material(size_t _shader_id, size_t _diffuse_id)
      : shader_id(_shader_id), diffuse_id(_diffuse_id), specular(0.5f),
        shininess(32.0f) {}

  Material(size_t _shader_id, size_t _diffuse_id, glm::vec3 _specular,
           float _shininess)
      : shader_id(_shader_id), diffuse_id(_diffuse_id), specular(_specular),
        shininess(_shininess) {}
};