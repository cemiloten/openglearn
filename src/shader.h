#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

namespace Shader
{

unsigned int create(const char* vert_source, const char* frag_source);
void use(unsigned int id);
void set_bool (const unsigned int id, const std::string& param, const bool  value);
void set_int  (const unsigned int id, const std::string& param, const int   value);
void set_float(const unsigned int id, const std::string& param, const float value);

}


#endif