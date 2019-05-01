#pragma once

#include <iostream>

#include "json.hpp"
#include "scene.hpp"
#include "tiny_gltf.h"

namespace gltf_loader {

struct BufferReader {
  const unsigned char* data;
  const size_t element_count;
  const size_t stride;

  BufferReader(const unsigned char* ptr, size_t elem_count, size_t byte_stride)
      : data(ptr), element_count(elem_count), stride(byte_stride) {}

  unsigned int operator[](size_t element) const {
    assert(element < element_count && "Out of bounds access");
    return *(reinterpret_cast<const unsigned int*>(data + element * stride));
  }
};

bool loadModel(tinygltf::Model& model, const char* filename);

} // namespace gltf_loader