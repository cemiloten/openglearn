#pragma once

#include <vector>
#include <string>

struct Vertex
{
    float px, py, pz;
    float nx, ny, nz;
    float tx, ty;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

union Triangle {
    Vertex v[3];
    char data[sizeof(Vertex) * 3];
};
