#include <iostream>

#include "glm/glm.hpp"
#include "gltf_loader.hpp"
#include "mesh.hpp"

using json = nlohmann::json;

namespace gltf_loader {

bool loadModel(const char* filename) {
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

  std::vector<Mesh> meshes(model.meshes.size());
  for (const auto& gltf_mesh : model.meshes) {
    VertexBuffer vertex_buffer;
    std::vector<unsigned int> index_buffer;

    for (const auto& primitive : gltf_mesh.primitives) {
      // Copy index buffer data into our mesh
      const auto& index_buffer_view = model.bufferViews[primitive.indices];
      const auto& gltf_index_buffer = model.buffers[index_buffer_view.buffer];

      index_buffer = copyBufferData<unsigned int>(gltf_index_buffer);

      // copy vertices into our mesh vertices
      for (const auto& attribute : primitive.attributes) {
        Attribute::Type type = Attribute::toType(attribute.first.c_str());
        if (type == Attribute::Type::None) {
          // error, not supported type
          exit(55);
        }

        // TODO: read this properly
        Attribute attr;
        attr.type = type;
        attr.element_count =
        attr.location = attribute.second;
      }
    }
    meshes.push_back(std::move(my_mesh));
  }

  return false;
}

template <typename T>
std::vector<T> copyBufferData(const tinygltf::Buffer& buffer) {
  size_t byte_size = buffer.data.size();
  std::vector<T> result = std::vector<T>(byte_size / sizeof(T));
  memcpy(result.data(), buffer.data.data(), byte_size);
  return result;
}

} // namespace gltf_loader
