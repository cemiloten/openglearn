#include "mesh.hpp"

Vertex::Vertex() : pos(0.0f), nrm(0.0f), tex(0.0f) {}

Vertex::Vertex(float vx, float vy, float vz, float nx, float ny, float nz,
               float tx, float ty)
    : pos(glm::vec3(vx, vy, vz)), nrm(glm::vec3(nx, ny, nz)),
      tex(glm::vec2(tx, ty)) {}

Vertex::Vertex(const glm::vec3& position, const glm::vec3& normal,
               const glm::vec2& texcoord)
    : pos(position), nrm(normal), tex(texcoord) {}

// Mesh::Mesh()
//     : vao(0), vbo(0), ebo(0), index_count(0), vertex_count(0),
//       mesh_data(nullptr) {}

// TODO: Steal mesh_data
// Mesh::Mesh(MeshData* mesh_data) {
//   glGenVertexArrays(1, &vao);
//   glGenBuffers(1, &vbo);
//   glGenBuffers(1, &ebo);

//   glBindVertexArray(vao);
//   glBindBuffer(GL_ARRAY_BUFFER, vbo);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh_data->vertices.size(),
//                mesh_data->vertices.data(),
//                GL_STATIC_DRAW);

//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//                mesh_data->indices.size() * sizeof(unsigned int),
//                mesh_data->indices.data(),
//                GL_STATIC_DRAW);

//   glEnableVertexAttribArray(0); // Positions
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

//   glEnableVertexAttribArray(1); // Normals
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
//                         (void*)offsetof(Vertex, nrm));

//   glEnableVertexAttribArray(2); // Texture coordinates
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
//                         (void*)offsetof(Vertex, tex));
//   glBindVertexArray(0);

//   index_count = static_cast<unsigned int>(mesh_data.indices.size());
//   vertex_count = static_cast<unsigned int>(mesh_data.vertices.size());
// }

// Mesh::Mesh(const MeshData& mesh_data) {
//   glGenVertexArrays(1, &vao);
//   glGenBuffers(1, &vbo);
//   glGenBuffers(1, &ebo);

//   glBindVertexArray(vao);
//   glBindBuffer(GL_ARRAY_BUFFER, vbo);
//   glBufferData(GL_ARRAY_BUFFER, mesh_data.vertices.size() * sizeof(Vertex),
//                mesh_data.vertices.data(),
//                GL_STATIC_DRAW); // Vertex data

//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//                mesh_data.indices.size() * sizeof(unsigned int),
//                mesh_data.indices.data(),
//                GL_STATIC_DRAW); // Indices

//   glEnableVertexAttribArray(0); // Positions
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

//   glEnableVertexAttribArray(1); // Normals
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
//                         (void*)offsetof(Vertex, nrm));

//   glEnableVertexAttribArray(2); // Texture coordinates
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
//                         (void*)offsetof(Vertex, tex));
//   glBindVertexArray(0);

//   index_count = static_cast<unsigned int>(mesh_data.indices.size());
//   vertex_count = static_cast<unsigned int>(mesh_data.vertices.size());
// }
