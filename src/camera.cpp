#include "camera.hpp"

Camera::Camera()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), right(glm::vec3(1.0f, 0.0f, 0.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)),
      world_up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(0.0f), pitch(0.0f) {}

void Camera::updateVectors() {
  front = glm::normalize(
      glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                sin(glm::radians(pitch)),
                sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
}