#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

#include "model.h"


Model::Model(const char* filename)
    : verts(), faces(), norms(), texcoords()
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
    }
}

int Model::nverts() const
{
    return (int)vertices.size();
}

int Model::nfaces() const
{
    return (int)faces.size();
}