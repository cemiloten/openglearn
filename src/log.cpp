#include <memory>

#include "log.h"

Log::Log(const std::string& path)
    : filename(path)
{
    if (instance == nullptr)
    {
        instance(new Log(filename));

        instance = std::make_unique<Log>();
        // static std::unique_ptr<Log> instance;
    }
}