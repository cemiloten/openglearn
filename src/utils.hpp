#pragma once

#include <fstream>
#include <string>

namespace utils {

std::string fileContentsToString(const char* filepath) {
  std::ifstream ifs(filepath);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  return content;
}

// std::string vert_source_;
// std::string frag_source_;
// std::ifstream vert_shader_file;
// std::ifstream frag_shader_file;
// vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
// frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
// try {
//   // open files
//   vert_shader_file.open(vert_path);
//   frag_shader_file.open(frag_path);
//   std::stringstream vert_shader_stream;
//   std::stringstream frag_shader_stream;
//   vert_shader_stream << vert_shader_file.rdbuf();
//   frag_shader_stream << frag_shader_file.rdbuf();
//   vert_shader_file.close();
//   frag_shader_file.close();
//   // convert stream into string
//   vert_source_ = vert_shader_stream.str();
//   frag_source_ = frag_shader_stream.str();
// } catch (std::ifstream::failure e) {
//   std::cout << "ERROR: Shader file not successfully read" << std::endl;
// }

} // namespace utils