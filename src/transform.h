#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Transform {
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale;
};