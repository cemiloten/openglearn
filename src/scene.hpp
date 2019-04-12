#pragma once

#include <limits>

#include "camera.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "transform.hpp"

// struct Handle {
//     unsigned int id;

//     Handle() : id(invalid_id) {}
//     inline bool isValid() { return id == invalid_id; }

//   private:
//     const static unsigned int invalid_id =
//         std::numeric_limits<unsigned int>::max();
// };

struct Instance {
  unsigned int mesh_id;
  unsigned int transform_id;

  Instance(unsigned int msh_id, unsigned int trs_id)
      : mesh_id(msh_id), transform_id(trs_id) {}
};

struct Scene {
public:
  std::vector<Mesh> meshes;
  std::vector<Instance> instances;
  // std::vector<Transform> transforms;
  // std::vector<Material> materials;
  // std::vector<Shader> shaders;

  Mesh mesh;
  Shader shader;
  Camera camera;

  Scene() : meshes(), instances(), shader(), camera() {}
};
