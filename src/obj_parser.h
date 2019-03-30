#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

#include "mesh.h"

namespace ObjParser
{

bool parse(const char* filepath, Mesh& mesh)
{
    std::ifstream in;
    in.open(filepath, std::ifstream::in);
    if (in.bad() || in.fail()) {
        std::cerr << "Failed to open " << filepath << std::endl;
        return false;
    }

    mesh = Mesh();
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (line.compare(0, 1, "#") == 0) {
            continue;
        }
        if (line.compare(0, 2, "v ") == 0) {
            iss >> trash;
            glm::vec3 v;
            for (int i = 0; i < 3; ++i) {
                iss >> v[i];
            }
            mesh.vertices.push_back(v);
        } else if (line.compare(0, 3, "vn ") == 0) {
            iss >> trash >> trash;
            glm::vec3 n;
            for (int i = 0; i < 3; ++i) {
                iss >> n[i];
            }
            mesh.normals.push_back(n);
        } else if (line.compare(0, 3, "vt ") == 0) {
            iss >> trash >> trash;
            glm::vec3 uv;
            for (int i = 0; i < 3; ++i) {
                iss >> uv[i];
            }
            mesh.texcoords.push_back(uv);
        } else if (line.compare(0, 2, "f ") == 0) {
            std::vector<glm::ivec3> f;
            glm::ivec3 temp;
            iss >> trash;
            while (iss >> temp[0] >> trash >> temp[1] >> trash >> temp[2]) {
                for (int i = 0; i < 3; ++i) {
                    temp[i]--;
                }
                f.push_back(temp);
            }
            assert(f.size() == 3);
            mesh.faces.push_back(f);
        }
    }
    return true;
}

} // ObjParser
