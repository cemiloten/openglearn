#pragma once

#include <string>

#include "glad/glad.h"

enum class TextureType : unsigned short int { Diffuse, Specular, Normal };

struct Texture {
  Texture(const std::string& path, TextureType _type);

  unsigned int texture_object;
  TextureType type;

  inline void bind() const { glBindTexture(GL_TEXTURE_2D, texture_object); }
};
