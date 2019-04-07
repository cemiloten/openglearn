#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "component.h"

struct Transform : public IComponent {
    glm::vec3 position;
    glm::quat quaternion;
    glm::vec3 scale;

    Transform()
        : position(glm::vec3(0.0f)), quaternion(glm::quat()),
          scale(glm::vec3(1.0f)) {}

    Transform(glm::vec3 pos, glm::quat quat, glm::vec3 scl)
        : position(pos), quaternion(quat), scale(scl) {}

    ComponentType get_type() const override { return ComponentType::Transform; }
};
