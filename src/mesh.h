#pragma once

#include <string>
#include <vector>

#include "freelist.h"
#include "glm/glm.hpp"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 nrm;
    glm::vec2 tex;

    Vertex();
    Vertex(const glm::vec3& position, const glm::vec3& normal,
           const glm::vec2& texcoord);
};

struct Mesh : public ListElement {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh() : vertices(), indices() {}
};

union Triangle {
    Vertex v[3];
    char data[sizeof(Vertex) * 3];
};
