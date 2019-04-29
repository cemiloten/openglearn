#include <iostream>

#include "json.hpp"
#include "gltf_loader.hpp"
#include "utils.hpp"

using json = nlohmann::json;

namespace gltf_loader {

bool loadModel(tinygltf::Model& model, const char* filename) {
  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename);

  if (!warn.empty()) {
    std::cerr << "WARN: " << warn << std::endl;
  }
  if (!err.empty()) {
    std::cerr << "ERR: " << err << std::endl;
  }

  if (!res) {
    std::cerr << "Failed to load glTF: " << filename << std::endl;
  } else {
    std::cout << "Loaded glTF: " << filename << std::endl;
  }

  return res;
}

} // namespace scene_loader
