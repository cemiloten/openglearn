#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;

    float yaw;
    float pitch;
    float zoom;

    Camera(glm::vec3 _position, glm::vec3 _up, glm::vec3 _front);
    glm::mat4 get_as_view_matrix();
};

#endif