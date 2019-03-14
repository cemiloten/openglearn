#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;  // the program ID

    //TODO: take in source instead of file path -> single responsibilty
    Shader(const char* vertexFilePath, const char* fragmentFilePath);

    void Use();

    void SetBool  (const std::string &name, const bool  value) const;
    void SetInt   (const std::string &name, const int   value) const;
    void SetFloat (const std::string &name, const float value) const;
};

#endif