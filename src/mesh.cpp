#include <iostream>
#include <cassert>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Mesh.h"

using namespace glm;

Mesh::Mesh()
    : vertices(), normals(), texcoords(), faces()
{
}

vec3& Mesh::get_point(int index)
{
    assert(index >= 0 && index < vertex_count());
    return vertices[index];
}

int Mesh::get_vertex(int face_index, int local_index) const
{
    assert(face_index  >= 0 && face_index  < face_count()
        && local_index >= 0 && local_index < 3);
    return faces[face_index][local_index].x;
}

vec2 Mesh::get_uv(int face_index, int local_index) const
{
    assert(face_index  >= 0 && face_index  < face_count()
        && local_index >= 0 && local_index < 3);
    return texcoords[faces[face_index][local_index].y];
}

vec3 Mesh::get_normal(int face_index, int local_index) const
{
    assert(face_index  >= 0 && face_index  < face_count()
        && local_index >= 0 && local_index < 3);
    return normals[faces[face_index][local_index].z];
}

Mesh load_mesh_from_obj(const std::string& path)
{
    // TODO
    // tinyobj::attrib_t attrib;
    // tinyobj::LoadObj()
}