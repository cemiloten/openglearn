#pragma once

#include <string>
#include <vector>

#include "freelist.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

struct Vertex {
  glm::vec3 pos;
  glm::vec3 nrm;
  glm::vec2 tex;

  Vertex();
  Vertex(const glm::vec3& position, const glm::vec3& normal,
         const glm::vec2& texcoord);
};

struct MeshData {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  MeshData();
};

struct Mesh {
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  unsigned int index_count;
  unsigned int vertex_count;

  Mesh();
  ~Mesh();
  Mesh(const MeshData& data);
};

union Triangle {
  Vertex v[3];
  char data[sizeof(Vertex) * 3];
};
