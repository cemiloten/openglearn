#include <iostream>

#include "obj_importer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh readObjFile(const std::string& path) {
    tinyobj::callback_t cb;
    cb.vertex_cb = readPosition;
    cb.normal_cb = readNormal;
    cb.texcoord_cb = readTexcoord;
    cb.index_cb = readIndex;

    std::ifstream ifs(path);
    if (ifs.fail()) {
        printf("file not found\n");
        exit(1);
    }

    std::cout << "starting to read " << path << std::endl;
    std::string warn;
    std::string err;

    ObjImporter importer;
    // bool ret = tinyobj::LoadObj(&attrib, &shapes, nullptr, &warn, &err,
    // path.c_str());
    bool ret =
        tinyobj::LoadObjWithCallback(ifs, cb, &importer, NULL, &warn, &err);

    if (!warn.empty()) {
        std::cout << "WARN:\n" << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "ERR:\n" << err << std::endl;
    }
    if (!ret) {
        std::cout << "Couldn't read file: " << path << std::endl;
        exit(1);
    }

    return importer.mesh;
}

void readPosition(void* userData, float x, float y, float z, float w) {
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);
    imp->positions.push_back(Vector3(x, y, z));
}

void readNormal(void* userData, float x, float y, float z) {
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);
    imp->normals.push_back(Vector3(x, y, z));
}

void readTexcoord(void* userData, float x, float y, float z) {
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);
    imp->texcoords.push_back(Vector2(x, y));
}

void readIndex(void* userData, tinyobj::index_t* indices, int numIndices) {
    assert(numIndices == 3 && "Only triangles are supported when reading objs");
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);

    for (int i = 0; i < numIndices; ++i) {
        tinyobj::index_t idx = indices[i];
        tinyobj::index_t cleanIdx;

        tinyobj::fixIndex(idx.vertex_index, imp->indexReadCount,
                          &cleanIdx.vertex_index);
        ++imp->indexReadCount;
        tinyobj::fixIndex(idx.normal_index, imp->indexReadCount,
                          &cleanIdx.normal_index);
        ++imp->indexReadCount;
        tinyobj::fixIndex(idx.texcoord_index, imp->indexReadCount,
                          &cleanIdx.texcoord_index);
        ++imp->indexReadCount;

        int index = imp->findVertex(cleanIdx);
        if (index != -1) {
            imp->mesh.indices.push_back(index);
        } else {
            Vertex vertex(imp->positions[cleanIdx.vertex_index],
                          imp->normals[cleanIdx.normal_index],
                          imp->texcoords[cleanIdx.texcoord_index]);

            imp->mesh.indices.push_back(
                static_cast<unsigned int>(imp->mesh.vertices.size()));
            imp->mesh.vertices.push_back(vertex);

            imp->vertexIndices.push_back(cleanIdx);
        }
    }
}

int ObjImporter::findVertex(tinyobj::index_t vertex) {
    for (size_t i = 0; i < vertexIndices.size(); ++i) {
        const tinyobj::index_t& v = vertexIndices[i];
        if (v.vertex_index == vertex.vertex_index &&
            v.normal_index == vertex.normal_index &&
            v.texcoord_index == vertex.texcoord_index) {
            return i;
        }
    }
    return -1;
}