#include "camera.h"

Camera::Camera(
    glm::vec3 _position,
    glm::vec3 _up,
    glm::vec3 _front)
        : position (_position)
        , up       (_up)
        , front    (_front)
        , yaw      (0.0f)
        , pitch    (0.0f)
        , zoom     (0.0f)
{
    right = glm::cross(front, up);
}

glm::mat4 Camera::get_as_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}