#pragma once

#include <iostream>

#include "json.hpp"
#include "scene.hpp"
#include "utils.hpp"

using json = nlohmann::json;

namespace scene_loader {

Scene* load(const std::string& scene_file_path) {
  std::string content = utils::fileToString(scene_file_path);
  auto js = json::parse(content);
  Scene* scene = new Scene;
  // for (auto& thing : js["models"]) {
  //   std::cout << thing << std::endl;
  // }

  return scene;

    // _scene = new Scene;

    // _scene->camera = Camera();
    // _scene->camera.position += glm::vec3(0.0f, 2.0f, 2.0f);
    // _scene->camera.pitch -= 45.0f;

    // MeshData mesh_data = readObjFile(obj_path);
    // _scene->meshes.push_back(Mesh(mesh_data));

    // _scene->shaders.push_back(
    //     Shader("data/shaders/phong.vert", "data/shaders/phong.frag"));
    // _scene->shaders.push_back(
    //     Shader("data/shaders/light.vert", "data/shaders/light.frag"));

    // _scene->textures.push_back(
    //     Texture("data/textures/container2.png", TextureType::Diffuse));

    // _scene->textures.push_back(Texture("data/textures/container2_specular.png",
    //                                    TextureType::Specular));

    // _scene->transforms.resize(2);
    // _scene->transforms[1].translation += glm::vec3(1.3f, 1.3f, -1.3f);
    // _scene->transforms[1].scale *= 0.3f;

    // _scene->materials.push_back(Material(0, 0, 0));
    // _scene->materials.push_back(Material(1, 0, 0));

    // _scene->instances.push_back(Instance(0, 0, 0));
    // _scene->instances.push_back(Instance(0, 1, 1));
}

} // namespace SceneLoader