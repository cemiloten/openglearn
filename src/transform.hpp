#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

struct Transform {
  glm::vec3 translation;
  glm::quat rotation;
  glm::vec3 scale;

  Transform()
      : translation(glm::vec3(0.0f)), rotation(glm::quat(0, 0, 0, 1)),
        scale(glm::vec3(1.0f)) {}

  Transform(glm::vec3 _translation, glm::quat _rotation, glm::vec3 _scale)
      : translation(_translation), rotation(_rotation), scale(_scale) {}
};