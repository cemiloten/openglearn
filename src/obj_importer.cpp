#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "obj_importer.h"
#include "tiny_obj_loader.h"

namespace obj_importer {

Mesh read_obj_file(const std::string &path) {
  tinyobj::callback_t cb;
  cb.vertex_cb = vertexCallback;
  cb.normal_cb = normalCallback;
  cb.texcoord_cb = texcoordCallback;
  cb.index_cb = indexCallback;
  cb.group_cb = groupCallback;
  cb.object_cb = objectCallback;

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

  // Passing NULL to MaterialFileReader parameter because we don't need it for
  // this exercise.
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


  // printf("Mesh has positions: %d", mesh.hasPositions());
  // printf("Mesh has normals: %d", mesh.hasNormals());
  // printf("Mesh has uvs: %d", mesh.hasTexcoords());

  return mesh;
}

void vertexCallback(void *userData, tinyobj::real_t x, tinyobj::real_t y,
                    tinyobj::real_t z, tinyobj::real_t w) {
  Mesh *mesh = reinterpret_cast<Mesh *>(userData);
}

void texcoordCallback(void *userData, tinyobj::real_t x, tinyobj::real_t y,
                      tinyobj::real_t z) {
  Mesh *mesh = reinterpret_cast<Mesh *>(userData);
}

void normalCallback(void *userData, tinyobj::real_t x, tinyobj::real_t y,
                    tinyobj::real_t z) {
  Mesh *mesh = reinterpret_cast<Mesh *>(userData);
}

void indexCallback(void *userData, tinyobj::index_t *indices, int numIndices) {
  // Support only triangles
  if (numIndices != 3) {
    return;
  }
  Mesh *mesh = reinterpret_cast<Mesh *>(userData);
}

void groupCallback(void *userData, const char **names, int numNames) {
  // MyMesh *mesh = reinterpret_cast<MyMesh*>(userData);
  printf("group : name = \n");

  for (int i = 0; i < numNames; i++) {
    printf("  %s\n", names[i]);
  }
}

void objectCallback(void *userData, const char *name) {
  // MyMesh *mesh = reinterpret_cast<MyMesh*>(user_data);
  printf("object : name = %s\n", name);
}

}