#include <iostream>

#include "obj_importer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace obj_importer {

Mesh read_obj_file(const std::string &path) {
    tinyobj::callback_t cb;
    cb.vertex_cb = read_position;
    cb.normal_cb = read_normal;
    cb.texcoord_cb = read_texcoord;
    cb.index_cb = read_index;

    const char *path_ = path.c_str();
    std::ifstream ifs(path_);
    if (ifs.fail()) {
        // TODO: log
        printf("file not found\n");
        exit(1);
    }

    printf("Starting to read %s\n", path_);
    std::string warn;
    std::string err;
    Mesh mesh;

    bool ret = tinyobj::LoadObjWithCallback(ifs, cb, &mesh, NULL, &warn, &err);

    if (!warn.empty()) {
        std::cout << "WARN:\n" << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "ERR:\n" << err << std::endl;
    }
    if (!ret) {
        printf("Couldn't read file: %s", path_);
        exit(1);
    }

    return mesh;
}

void read_vertex(void *user_data, float x, float y, float z, float w) {
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(user_data);
    imp->positions.push_back(Vector3(x, y, z));
}

void read_normal(void *user_data, float x, float y, float z) {
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(user_data);
    imp->normals.push_back(Vector3(x, y, z));
}

void read_texcoord(void *user_data, float x, float y, float z) {
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(user_data);
    imp->texcoords.push_back(Vector2(x, y));
}

void read_index(void *user_data, tinyobj::index_t* indices, int num_indices) {
    assert(num_indices == 3 && "Only triangles are supported when reading objs");
    ObjImporter* imp = reinterpret_cast<ObjImporter*>(user_data);

    for (int i = 0; i < num_indices; ++i)
    {
        tinyobj::index_t idx = indices[i];
        tinyobj::index_t cleanIdx;

        tinyobj::fixIndex(idx.vertex_index, imp->indexReadCount, &cleanIdx.vertex_index);
        ++imp->indexReadCount;
        tinyobj::fixIndex(idx.normal_index, imp->indexReadCount, &cleanIdx.normal_index);
        ++imp->indexReadCount;
        tinyobj::fixIndex(idx.texcoord_index, imp->indexReadCount, &cleanIdx.texcoord_index);
        ++imp->indexReadCount;

        int index = imp->findVertex(cleanIdx);
        if (index != -1) {
           imp->mesh.indices.push_back(index);
        } else {
            Vertex vertex(
               imp->positions[cleanIdx.vertex_index],
               imp->normals  [cleanIdx.normal_index],
               imp->texcoords[cleanIdx.texcoord_index]);

           imp->mesh.indices.push_back(static_cast<unsigned int>(imp->mesh.vertices.size()));
           imp->mesh.vertices.push_back(vertex);

           imp->vertexIndices.push_back(cleanIdx);
        }
    }
}

int ObjImporter::findVertex(tinyobj::index_t vertex) {
    for (size_t i = 0; i < vertexIndices.size(); ++i) {
        const tinyobj::index_t& v = vertexIndices[i];
        if (v.vertex_index == vertex.vertex_index
            && v.normal_index == vertex.normal_index
            && v.texcoord_index == vertex.texcoord_index) {
                return i;
        }
    }
    return -1;
}

}