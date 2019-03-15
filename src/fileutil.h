#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include <stdio.h>
#include <stdlib.h>

namespace FileUtil
{

const char* get_file_content(const char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        return NULL;
    }

    char c;
    const char* content = new char[sizeof]
    while ((c = fgetc(fp)) != EOF) {

    }

    return content;
}

// const std::string get_file_content(const char* path)
// {
//     std::ifstream file(path, std::ios::binary);
//     std::string content;
//     content.assign(std::istreambuf_iterator<char>(file),
//                    std::istreambuf_iterator<char>());
//     return content;
// }

};

#endif