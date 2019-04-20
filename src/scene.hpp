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
  Handle material;

  Instance() : mesh(), transform(), material() {}

  Instance(unsigned int mesh_handle, unsigned int transform_handle)
      : mesh(Handle(mesh_handle)), transform(Handle(transform_handle)) {}

  Instance(unsigned int mesh_handle, unsigned int transform_handle,
           unsigned int material_handle)
      : mesh(Handle(mesh_handle)), transform(Handle(transform_handle)),
        material(Handle(material_handle)) {}
};

struct Scene {
public:
  std::vector<Mesh> meshes;
  std::vector<Instance> instances;
  std::vector<Transform> transforms;
  std::vector<Shader> shaders;
  std::vector<Material> materials;
  std::vector<Texture> textures;

  Camera camera;

  Scene() : meshes(), instances(), camera() {}

  inline const Mesh& getMesh(Instance instance) const {
    return meshes[instance.mesh.id];
  }

  inline const Transform& getTransform(Instance instance) const {
    return transforms[instance.transform.id];
  }

  inline const Material& getMaterial(Instance instance) const {
    return materials[instance.material.id];
  }

  inline const Shader& getShader(Material material) const {
    return shaders[material.shader_id];
  }
};
