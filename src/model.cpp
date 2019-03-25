#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

#include "model.h"

using namespace glm;

Model::Model(const char* filename)
    : vertices(), normals(), texcoords(), faces()
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.bad() || in.fail) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (line.compare(0, 2, "v ") == 0) {
            iss >> trash;
            vec3 v;
            for (int i = 0; i < 3; ++i) {
                iss >> v[i];
            }
            vertices.push_back(v);
        } else if (line.compare(0, 3, "vn ") == 0) {
            iss >> trash >> trash;
            vec3 n;
            for (int i = 0; i < 3; ++i) {
                iss >> n[i];
            }
            normals.push_back(n);
        } else if (line.compare(0, 3, "vt ") == 0) {
            iss >> trash >> trash;
            vec3 uv;
            for (int i = 0; i < 3; ++i) {
                iss >> uv[i];
            }
            texcoords.push_back(uv);
        } else if (line.compare(0, 2, "f ") == 0) {
            std::vector<ivec3> f;
            ivec3 temp;
            iss >> trash;
            while (iss >> temp[0] >> trash >> temp[1] >> trash >> temp[2]) {
                for (int i = 0; i < 3; ++i) {
                    temp[i]--;
                }
                f.push_back(temp);
            }
            assert(f.size() == 3);
            faces.push_back(f);
        }
    }
    std::cerr << "# v# " << vertices.size() << " f# " << faces.size() << std::endl;
}

int Model::vertex_count() const
{
    return (int)vertices.size();
}

int Model::face_count() const
{
    return (int)faces.size();
}

vec3& Model::get_point(int index)
{
    assert(index >= 0 && index < vertex_count());
    return vertices[index];
}

int Model::get_vertex(int face_index, int local_index) const
{
    assert(face_index  >= 0 && face_index  < face_count()
        && local_index >= 0 && local_index < 3);
    return faces[face_index][local_index].x;
}

vec2 Model::get_uv(int face_index, int local_index) const
{
    assert(face_index  >= 0 && face_index  < face_count()
        && local_index >= 0 && local_index < 3);
    return texcoords[faces[face_index][local_index].y];
}

vec3 Model::get_normal(int face_index, int local_index) const
{
    assert(face_index  >= 0 && face_index  < face_count()
        && local_index >= 0 && local_index < 3);
    return normals[faces[face_index][local_index].z];
}