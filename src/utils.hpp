#pragma once

#include <fstream>
#include <string>

#include "json.hpp"

namespace utils {

std::string fileToString(const std::string& filepath) {
  std::ifstream ifs(filepath);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  return content;
}

nlohmann::json jsonFromFile(const std::string& filepath) {
  return nlohmann::json::parse(fileToString(filepath));
}

} // namespace utils