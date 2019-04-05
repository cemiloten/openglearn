#pragma once

#include <string>

#include "tiny_obj_loader.h"
#include "mesh.h"

namespace obj_importer {

Mesh read_obj_file(const std::string& path);
void read_position(void* user_data, float x, float y, float z, float w);
void read_texcoord(void* user_data, float x, float y, float z);
void read_normal  (void* user_data, float x, float y, float z);
void read_index   (void* user_data, tinyobj::index_t* indices, int num_indices);
void read_object  (void* user_data, const char* name);

struct ObjImporter {
    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> texcoords;
    std::vector<tinyobj::index_t> vertices;
    Mesh mesh;
};

bool operator==(const tinyobj::index_t& lhs, const tinyobj::index_t& rhs);

}