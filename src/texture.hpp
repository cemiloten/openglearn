#pragma once

#include <string>

#include "glad/glad.h"

enum class TextureType : unsigned short int { None, Diffuse, Specular, Normal };

struct Texture {
  Texture(const std::string& path, TextureType _type);
  Texture(const std::string& path, const std::string& _type);

  unsigned int texture_object;
  TextureType type;

  inline void bind() const { glBindTexture(GL_TEXTURE_2D, texture_object); }

private:
  Texture(const std::string& path);
};
