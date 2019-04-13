#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

struct Vertex {
  glm::vec3 pos;
  glm::vec3 nrm;
  glm::vec2 tex;

  Vertex();
  Vertex(float vx, float vy, float vz, float nx, float ny, float nz, float tx,
         float ty);
  Vertex(const glm::vec3& position, const glm::vec3& normal,
         const glm::vec2& texcoord);
};

struct MeshData {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  MeshData();
  MeshData(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices)
      : vertices(_vertices), indices(_indices) {}
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
