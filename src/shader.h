#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Shader
{

unsigned int create(const char* vert_source, const char* frag_source);
void use(unsigned int id);
void set_bool  (const unsigned int id, const std::string& param, const bool  value);
void set_int   (const unsigned int id, const std::string& param, const int   value);
void set_float (const unsigned int id, const std::string& param, const float value);
void set_vec2  (const unsigned int id, const std::string& param, const glm::vec2& value);
void set_vec3  (const unsigned int id, const std::string& param, const glm::vec3& value);
void set_vec4  (const unsigned int id, const std::string& param, const glm::vec4& value);
void set_vec2  (const unsigned int id, const std::string& param, const float x, const float y);
void set_vec3  (const unsigned int id, const std::string& param, const float x, const float y, const float z);
void set_vec4  (const unsigned int id, const std::string& param, const float x, const float y, const float z, const float w);
void set_mat2  (const unsigned int id, const std::string& param, const glm::mat2& mat);
void set_mat3  (const unsigned int id, const std::string& param, const glm::mat3& mat);
void set_mat4  (const unsigned int id, const std::string& param, const glm::mat4& mat);

}
