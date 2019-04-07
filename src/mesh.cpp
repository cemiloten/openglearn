#include "mesh.h"

Vertex::Vertex() : pos(0.0f), nrm(0.0f), tex(0.0f) {}

Vertex::Vertex(const Vector3 &position, const Vector3 &normal,
               const Vector2 &texcoord)
    : pos(position), nrm(normal), tex(texcoord) {}