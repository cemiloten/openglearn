
// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "freelist.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"

struct Instance {
    unsigned int mesh_id;
    unsigned int transform_id;
};

class Scene {
  public:
    std::vector<Mesh> _meshes;

    // FreeList<Mesh> _meshes;
    // FreeList<Transform> _transforms;
    // FreeList<Instance> _instances;
    // FreeList<Shader> _shaders;
    // FreeList<Material> _materials;

    Scene();
};
