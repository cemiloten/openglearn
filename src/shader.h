#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

struct Shader {
    Shader(const char* vert_source, const char* frag_source);

    void use();

    unsigned int id;
};
