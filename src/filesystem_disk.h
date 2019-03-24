#pragma once

struct FileSystem
{
    FileSystem() {};
    virtual ~FileSystem() {};
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem)  = delete;

    virtual File* open(const char* path, Fil)
}