#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "obj_importer.h"
#include "tiny_obj_loader.h"

namespace obj_importer {

Mesh read_obj_file(const std::string &path) {
    tinyobj::callback_t cb;
    cb.object_cb = read_object;
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
    ObjImporter* importer = reinterpret_cast<ObjImporter*>(user_data);
    importer->positions.push_back(Vector3(x, y, z));
}

void read_normal(void *user_data, float x, float y, float z) {
    ObjImporter* importer = reinterpret_cast<ObjImporter*>(user_data);
    importer->normals.push_back(Vector3(x, y, z));
}

void read_texcoord(void *user_data, float x, float y, float z) {
    ObjImporter* importer = reinterpret_cast<ObjImporter*>(user_data);
    importer->texcoords.push_back(Vector2(x, y));
}

void read_index(void *user_data, tinyobj::index_t* indices, int num_indices) {
    assert(num_indices == 3 && "Only triangles are supported when reading objs");
    ObjImporter* importer = reinterpret_cast<ObjImporter*>(user_data);
}

void read_object(void *user_data, const char *name) {
    printf("object : name = %s\n", name);
}

bool operator==(const tinyobj::index_t& lhs, const tinyobj::index_t& rhs) {
    return lhs.vertex_index == rhs.vertex_index
        && lhs.normal_index == rhs.normal_index
        && lhs.texcoord_index == rhs.texcoord_index;
}

} // namespace obj_importer