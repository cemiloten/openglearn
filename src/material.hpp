#pragma once

#include "glm/vec3.hpp"
#include "texture.hpp"

struct Material {
  size_t shader_id;
  size_t diffuse_id;
  size_t specular_id;

  float shininess;

  Material(size_t _shader_id, size_t _diffuse_id, size_t _specular_id,
           float _shininess = 32.0f)
      : shader_id(_shader_id), diffuse_id(_diffuse_id),
        specular_id(_specular_id), shininess(_shininess) {}
};