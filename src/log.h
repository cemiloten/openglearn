#pragma once

#include <string>

struct Log {
public:
    Log(const std::string& path = "log.json");

    void commit(const std::string& path = "");

private:
    std::string filename;
    static std::unique_ptr<Log> instance;
    // static Log* instance;

    Log(Log const&) = delete;
    void operator=(Log const&) = delete;
};