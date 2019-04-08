#pragma once

#include <string>

#include "mesh.h"
#include "tiny_obj_loader.h"

Mesh readObjFile(const std::string& path);
void readPosition(void* userData, float x, float y, float z, float w);
void readTexcoord(void* userData, float x, float y, float z);
void readNormal(void* userData, float x, float y, float z);
void readIndex(void* userData, tinyobj::index_t* indices, int numIndices);

struct ObjImporter {
    ObjImporter()
        : positions(), normals(), texcoords(), vertexIndices(),
          indexReadCount(0), mesh() {}

    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> texcoords;
    std::vector<tinyobj::index_t> vertexIndices;
    int indexReadCount;

    Mesh mesh;

    int findVertex(tinyobj::index_t vertex);
};