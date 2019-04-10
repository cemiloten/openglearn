#pragma once

#include <string>

#include "glm/glm.hpp"
#include "mesh.h"
#include "tiny_obj_loader.h"

MeshData readObjFile(const std::string& path);
void readPosition(void* userData, float x, float y, float z, float w);
void readTexcoord(void* userData, float x, float y, float z);
void readNormal(void* userData, float x, float y, float z);
void readIndex(void* userData, tinyobj::index_t* indices, int numIndices);

struct ObjImporter {
    ObjImporter()
        : positions(), normals(), texcoords(), vertex_indices(),
          index_read_count(0), mesh_data() {}

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<tinyobj::index_t> vertex_indices;
    int index_read_count;

    MeshData mesh_data;

    int findVertex(tinyobj::index_t vertex);
};