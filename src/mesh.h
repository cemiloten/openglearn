#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "component.h"

struct Mesh : public Component
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> texcoords;
    std::vector<std::vector<glm::ivec3> > faces; // this ivec3 means vertex/uv/normal ids

    Mesh() : vertices() , normals() , texcoords() , faces()
    {}

    // int vertex_count() const;
    // int face_count() const;

    // glm::vec3& get_point  (int index);
    // int        get_vertex (int face_index, int local_index) const;
    // glm::vec2  get_uv     (int face_index, int local_index) const;
    // glm::vec3  get_normal (int face_index, int local_index) const;

    ComponentType get_type() const override
    {
        return ComponentType::Mesh;
    }
};


