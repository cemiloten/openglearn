#pragma once

#include <iostream>

#include "json.hpp"
#include "scene.hpp"
#include "tiny_gltf.h"

namespace gltf_loader {

bool loadModel(tinygltf::Model& model, const char* filename);

} // namespace scene_loader