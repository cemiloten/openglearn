#pragma once

#include <string>

#include "json.hpp"

namespace utils {

std::string fileToString(const std::string& filepath);

nlohmann::json jsonFromFile(const std::string& filepath);

} // namespace utils