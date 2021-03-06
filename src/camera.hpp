#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Camera {
  glm::vec3 position;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 front;
  glm::vec3 world_up;

  float pitch;
  float yaw;

  Camera();

  inline glm::mat4 getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
  }

  void updateVectors();
};