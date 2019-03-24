#pragma once

#include "types.h"

struct FileOpenMode
{
    enum Enum
    {
        READ,
        WRITE
    };
};

struct File
{
    File() {}
    virtual ~File() {}

    virtual void open(const char* path, FileOpenMode::Enum mode) = 0;
    virtual void close()                                         = 0;
    virtual bool is_open()                                       = 0;
    virtual u32  cursor_position()                               = 0;
    virtual bool end_of_file()                                   = 0;
    virtual void seek(u32 position)                              = 0;
    virtual void seek_to_end()                                   = 0;
    virtual void skip(u32 byte_count)                            = 0;
    virtual u32  read(void* data, u32 size)                      = 0;
    virtual u32  write(const void* data, u32 size)               = 0;
    virtual void flush()                                         = 0;
}