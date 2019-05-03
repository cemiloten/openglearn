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
        AttributeType type = Attribute::toType(attribute.first.c_str());
        if (type == AttributeType::None) {
          // error, not supported type
          exit(55);
        }

        tinygltf::Accessor accessor = model.accessors[attribute.second];

        // TODO: read this properly
        Attribute attr;
        attr.type = type;
        attr.element_count = // VEC3 or VEC2 to type
            attr.byte_size = attr.offset = accessor.byteOffset;
        attr.location = attribute.second;
      }
    }
    meshes.push_back(Mesh(vertex_buffer, index_buffer));
  }

  return false;
}

size_t countFromType(const char* type) {
  if (!strcmp("VEC2", type)) {
    return TINYGLTF_TYPE_VEC2;
  }
  if (!strcmp("VEC3", type)) {
    return TINYGLTF_TYPE_VEC3;
  }
  if (!strcmp("VEC4", type)) {
    return TINYGLTF_TYPE_VEC4;
  }
  return -1;
}

template <typename T>
std::vector<T> copyBufferData(const tinygltf::Buffer& buffer) {
  size_t byte_size = buffer.data.size();
  std::vector<T> result = std::vector<T>(byte_size / sizeof(T));
  memcpy(result.data(), buffer.data.data(), byte_size);
  return result;
}

} // namespace gltf_loader
