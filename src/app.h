#pragma once

class IApp
{
public:
    IApp(const char* _name, const char* _description)
        : m_name(_name), m_description(_description)
    {}

    virtual ~IApp() = 0;

    virtual void init(
        int _argc,
        const char* const* _argv,
        unsigned int _width,
        unsigned int _height
    ) = 0;

    virtual int shutdown() = 0;

    virtual bool update() = 0;

    const char* get_name() const { return m_name; }

    const char* get_description() const { return m_description; }


private:
    const char* m_name;
    const char* m_description;
};