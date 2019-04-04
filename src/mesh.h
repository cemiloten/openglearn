#pragma once

#include <vector>
#include <string>

#include "vector3.h"
#include "vector2.h"

struct Vertex {
    Vector3 pos;
    Vector3 nrm;
    Vector2 uv;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

union Triangle {
    Vertex v[3];
    char data[sizeof(Vertex) * 3];
};
