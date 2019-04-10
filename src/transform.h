#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Transform {
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale;

    Transform()
        : translation(glm::vec3(0.0f)), rotation(/*TODO identity*/),
          scale(glm::vec3(0.0f)) {}
};