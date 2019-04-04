#pragma once

#include <string>

#include "tiny_obj_loader.h"
#include "mesh.h"

namespace obj_importer {

Mesh read_obj_file(const std::string& path);
void vertexCallback  (void* user_data, float x, float y, float z, float w);
void texcoordCallback(void* user_data, float x, float y, float z);
void normalCallback  (void* user_data, float x, float y, float z);
void indexCallback   (void* user_data, tinyobj::index_t* indices, int num_indices);
void groupCallback   (void* user_data, const char** names, int num_names);
void objectCallback  (void* user_data, const char* name);

}