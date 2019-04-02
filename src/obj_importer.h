#pragma once

#include <string>

#include "tiny_obj_loader.h"
#include "mesh.h"

namespace obj_importer {

Mesh read_obj_file(const std::string& path);
void vertexCallback  (void *userData, float x, float y, float z, float w);
void texcoordCallback(void *userData, float x, float y, float z);
void normalCallback  (void *userData, float x, float y, float z);
void indexCallback   (void *userData, tinyobj::index_t *indices, int numIndices);
void groupCallback   (void* userData, const char** names, int numNames);
void objectCallback  (void *userData, const char *name);

}