#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "freelist.h"
#include "mesh.h"

class Scene {
   public:
    FreeList<Mesh> _meshes;
    // FreeList<Transform> _transforms;
    // FreeList<Instance> _instances;
};