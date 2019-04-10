#pragma once

#include "glm/glm.hpp"

class Camera {
    glm::vec3 position;

    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 world_up;

    float yaw;
    float pitch;
};