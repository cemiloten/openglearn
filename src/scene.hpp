#pragma once

#include <limits>

#include "camera.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "transform.hpp"

struct Handle {
  unsigned short int id;

  Handle() : id(invalid_id) {}
  Handle(unsigned short int _id) : id(_id) {}

  inline bool isValid() { return id == invalid_id; }

private:
  const static unsigned int invalid_id =
      std::numeric_limits<unsigned short int>::max();
};

struct Instance {
  Handle mesh;
  Handle transform;

  Instance() : mesh(), transform() {}
  Instance(unsigned int mesh_handle, unsigned int transform_handle)
      : mesh(Handle(mesh_handle)), transform(Handle(transform_handle)) {}
};

struct Scene {
public:
  std::vector<Mesh> meshes;
  std::vector<Instance> instances;
  std::vector<Transform> transforms;
  // std::vector<Material> materials;
  // std::vector<Shader> shaders;

  Shader shader;
  Camera camera;

  Scene() : meshes(), instances(), shader(), camera() {}
};
