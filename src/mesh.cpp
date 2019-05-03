#include "mesh.hpp"

AttributeType Attribute::toType(const char* attribute) {
  if (!strcmp("POSITION", attribute)) {
    return AttributeType::Position;
  }
  if (!strcmp("NORMAL", attribute)) {
    return AttributeType::Normal;
  }
  if (!strcmp("TEXCOORD_0", attribute)) {
    return AttributeType::Texcoord;
  }
  return AttributeType::None;
}

Mesh::Mesh(const VertexBuffer& vtx_buffer,
           const std::vector<unsigned int>& idx_buffer)
    : vertex_buffer(vtx_buffer), index_buffer(idx_buffer) {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_buffer.vertices.size(),
               vertex_buffer.vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * index_buffer.size(), index_buffer.data(),
               GL_STATIC_DRAW);

  for (const auto& attribute : vertex_buffer.attributes) {
    glEnableVertexAttribArray(attribute.location);
    glVertexAttribPointer(attribute.location, attribute.element_count, GL_FLOAT,
                          GL_FALSE, vertex_buffer.stride,
                          (void*)attribute.offset);
  }
  glBindVertexArray(0);
}
