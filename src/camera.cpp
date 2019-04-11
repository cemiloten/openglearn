#include "camera.h"

Camera::Camera()
    : position(glm::vec3(0.0f)), right(glm::vec3(1.0f, 0.0f, 0.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)), world_up(glm::vec3(0.0f, 1.0f, 0.0f)),
      yaw(0.0f), pitch(0.0f) {
  front = glm::cross(right, up);
}