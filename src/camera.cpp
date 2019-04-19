#include "camera.hpp"

Camera::Camera()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
      world_up(up), pitch(0.0f), yaw(0.0f) {
  updateVectors();
}

void Camera::updateVectors() {
  float _yaw = glm::radians(yaw);
  float _pitch = glm::radians(pitch);

  // Calculate the new front vector.
  glm::vec3 _front;
  _front.x = -sin(_yaw) * cos(_pitch);
  _front.y = sin(_pitch);
  _front.z = -cos(_yaw) * cos(_pitch);
  front = glm::normalize(_front);

  // Update right and up vector from new calculation.
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
}