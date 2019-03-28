#pragma once

struct IApp
{
public:
    IApp(const char* _name, const char* _description)
        : m_name(_name), m_description(_description)
    {}

    virtual ~IApp() = 0;

    virtual void initialize(
        const int _argc,
        const char* const* _argv,
        const unsigned int _width,
        const unsigned int _height)
    {
        m_width = _width;
        m_height = _height;
    }

    virtual int shutdown() = 0;

    virtual bool update() = 0;

    const char* get_name() const { return m_name; }

    const char* get_description() const { return m_description; }

protected:
    unsigned int m_width;
    unsigned int m_height;

private:
    const char* m_name;
    const char* m_description;
};