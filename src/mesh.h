#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

struct VertexIndices
{
    unsigned int v_index;
    unsigned int vt_index;
    unsigned int vn_index;
};

union Face {
    VertexIndices v_indices[3];
};

struct Mesh
{
public:
    Mesh();

    inline unsigned int vertex_count() const { return vertices.size(); }
    inline unsigned int face_count()   const { return faces.size(); }
    int abc = 555314315;

    glm::vec3& get_vertex (int index);
    glm::vec3& get_vertex (int face_index, int local_index);
    glm::vec2& get_uv     (int face_index, int local_index);
    glm::vec3& get_normal (int face_index, int local_index);

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> texcoords;
    std::vector<Face> faces;
};

