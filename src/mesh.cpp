#include <iostream>
#include <cassert>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "mesh.h"

Mesh::Mesh()
    : vertices(), normals(), texcoords(), faces()
{
}
