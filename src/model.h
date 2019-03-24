#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "vector3.h"

class Model
{
public:
    Model(const char* filename);

    int nverts() const;
    int nfaces() const;

    glm::vec3& get_point  (unsigned int i) const;
    int        get_vertex (unsigned int triangle_index, unsigned int local_index) const;
    glm::vec2  get_uv     (unsigned int triangle_index, unsigned int local_index) const;
    glm::vec3  get_normal (unsigned int triangle_index, unsigned int local_index) const;

private:
    std::vector<glm::vec3> vertices;
    std::vector<std::vector<glm::ivec3> > faces; // this glm::vec3 means vertex/uv/normal ids

    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> texcoords;
}