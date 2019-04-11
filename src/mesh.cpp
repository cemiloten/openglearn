#include "mesh.h"

Vertex::Vertex() : pos(0.0f), nrm(0.0f), tex(0.0f) {}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& normal,
               const glm::vec2& texcoord)
    : pos(position), nrm(normal), tex(texcoord) {}

MeshData::MeshData() : vertices(), indices() {}

Mesh::Mesh() : vao(0), vbo(0), ebo(0), index_count(0), vertex_count(0) {}

Mesh::Mesh(const MeshData& data) {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Vertex data
  glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(Vertex),
               data.vertices.data(), GL_STATIC_DRAW);

  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               data.indices.size() * sizeof(unsigned int), data.indices.data(),
               GL_STATIC_DRAW);

  // Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  // Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, nrm));
  // Texture coordinates
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, tex));
  glBindVertexArray(0);

  index_count = static_cast<unsigned int>(data.indices.size());
  vertex_count = static_cast<unsigned int>(data.vertices.size());
}

Mesh::~Mesh() {
  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
  // glDeleteBuffers(1, &ebo);
}
