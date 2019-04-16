#include <iostream>

#include "obj_importer.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

MeshData readObjFile(const std::string& path) {
  tinyobj::callback_t cb;
  cb.vertex_cb = readPosition;
  cb.normal_cb = readNormal;
  cb.texcoord_cb = readTexcoord;
  cb.index_cb = readIndex;

  std::ifstream ifs(path);
  if (ifs.fail()) {
    printf("OBJ file '%s' not found\n", path.c_str());
    exit(1);
  }

  std::string warn;
  std::string err;

  ObjImporter importer;
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

  return importer.mesh_data;
}

void readPosition(void* userData, float x, float y, float z, float w) {
  (void)w;
  ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);
  imp->positions.push_back(glm::vec3(x, y, z));
}

void readNormal(void* userData, float x, float y, float z) {
  ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);
  imp->normals.push_back(glm::vec3(x, y, z));
}

void readTexcoord(void* userData, float x, float y, float z) {
  (void)z;
  ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);
  imp->texcoords.push_back(glm::vec2(x, y));
}

void readIndex(void* userData, tinyobj::index_t* indices, int numIndices) {
  assert(numIndices == 3 && "Only triangles are supported when reading objs");
  ObjImporter* imp = reinterpret_cast<ObjImporter*>(userData);

  for (int i = 0; i < numIndices; ++i) {
    tinyobj::index_t idx = indices[i];
    tinyobj::index_t cleanIdx;

    tinyobj::fixIndex(idx.vertex_index, imp->index_read_count,
                      &cleanIdx.vertex_index);
    ++imp->index_read_count;
    tinyobj::fixIndex(idx.normal_index, imp->index_read_count,
                      &cleanIdx.normal_index);
    ++imp->index_read_count;
    tinyobj::fixIndex(idx.texcoord_index, imp->index_read_count,
                      &cleanIdx.texcoord_index);
    ++imp->index_read_count;

    int index = imp->findVertex(cleanIdx);
    if (index != -1) {
      imp->mesh_data.indices.push_back(index);
    } else {
      Vertex vertex(imp->positions[cleanIdx.vertex_index],
                    imp->normals[cleanIdx.normal_index],
                    imp->texcoords[cleanIdx.texcoord_index]);

      imp->mesh_data.indices.push_back(
          static_cast<unsigned int>(imp->mesh_data.vertices.size()));
      imp->mesh_data.vertices.push_back(vertex);

      imp->vertex_indices.push_back(cleanIdx);
    }
  }
}

int ObjImporter::findVertex(tinyobj::index_t vertex) {
  for (size_t i = 0; i < vertex_indices.size(); ++i) {
    const tinyobj::index_t& v = vertex_indices[i];
    if (v.vertex_index == vertex.vertex_index &&
        v.normal_index == vertex.normal_index &&
        v.texcoord_index == vertex.texcoord_index) {
      return i;
    }
  }
  return -1;
}