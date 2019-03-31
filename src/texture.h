#pragma once
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Texture
{

GLuint load(const std::string& imagepath)
{
    std::cout << "Texture::load(\"" << imagepath << "\");" << std::endl;

    stbi_set_flip_vertically_on_load(1);
    int width;
    int height;
    int bytes_per_pixel;
    unsigned char* data = stbi_load(imagepath.c_str(), &width, &height, &bytes_per_pixel, 3);
    if (!data) {
        std::cerr << "Failed to load the texture (" << imagepath << ")" << std::endl;
        return -1;
    }
    GLuint textureID;
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    return textureID;
}

}