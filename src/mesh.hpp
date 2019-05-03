#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

enum class AttributeType { None, Position, Normal, Texcoord };

struct Attribute {
  size_t byte_size;
  size_t element_count;
  size_t offset;
  int location;
  AttributeType type;

  static AttributeType toType(const char* attribute);
};

struct VertexBuffer {
  std::vector<float> vertices;
  std::vector<Attribute> attributes;
  size_t stride;
};

struct Mesh {
  VertexBuffer vertex_buffer;
  std::vector<unsigned int> index_buffer;

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  Mesh(const VertexBuffer& vtx_buffer,
       const std::vector<unsigned int>& idx_buffer);
};