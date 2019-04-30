#include "renderer.hpp"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"

namespace renderer {

struct GLProgramState {
  std::map<std::string, int> attributes;
  std::map<std::string, int> uniforms;
};

void drawMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh) {

}

void drawNode(const tinygltf::Model& model, const tinygltf::Node& node) {
  if (node.mesh > -1) {
    assert(node.mesh < model.meshes.size() &&
           "Invalid access: mesh index bigger than max value");
    drawMesh(model, model.meshes[node.mesh]);
  }
}

void drawModel(tinygltf::Model& model) {
  // TODO: draw gltf model here
  assert(model.scenes.size() > 0 && "Model does not contain any scene");
  int scene_to_display = model.defaultScene > -1 ? model.defaultScene : 0;
  const tinygltf::Scene& scene = model.scenes[scene_to_display];
  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    drawNode(model, model.nodes[scene.nodes[i]]);
  }
}

} // namespace renderer
