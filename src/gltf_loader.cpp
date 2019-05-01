#include <iostream>

#include "glm/glm.hpp"
#include "gltf_loader.hpp"
#include "json.hpp"
#include "utils.hpp"

using json = nlohmann::json;

namespace gltf_loader {

bool loadModel(const char* filename, std::vector<Mesh>* meshes) {
  tinygltf::Model model;
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
    return false;
  } else {
    std::cout << "Loaded glTF: " << filename << std::endl;
  }

  for (const auto& gltf_mesh : model.meshes) {
    MeshData mesh_data;
    Mesh mesh;
    // glm::vec3 min;
    // glm::vec3 max;

    for (const auto& mesh_primitive : gltf_mesh.primitives) {

      const auto& indices_accessor = model.accessors[mesh_primitive.indices];
      const auto& buffer_view = model.bufferViews[indices_accessor.bufferView];
      const auto& buffer = model.buffers[buffer_view.buffer];
      const auto data_address = buffer.data.data() + buffer_view.byteOffset +
                                indices_accessor.byteOffset;
      const auto byte_stride = indices_accessor.ByteStride(buffer_view);
      if (byte_stride < 0) {
        std::cerr << "Invalid byte stride in buffer view" << std::endl;
        return false;
      }

      if (indices_accessor.componentType !=
          TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
        std::cerr << "Only unsigned int is supported for now." << std::endl;
        return false;
      }

      BufferReader buffer_reader(data_address, indices_accessor.count,
                                 byte_stride);

      if (mesh_primitive.mode != TINYGLTF_MODE_TRIANGLES) {
        std::cerr << "Only triangles mode is supported for now." << std::endl;
        return false;
      }

      for (const auto& attribute : mesh_primitive.attributes) {
        if (attribute.first == "POSITION") {
        } else if (attribute.first == "NORMAL") {
        } else if (attribute.first == "TEXCOORD_0") {
        } else {
          // error
        }
      }
    }
  }

  return false;
}

} // namespace gltf_loader
