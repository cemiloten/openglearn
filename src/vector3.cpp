
#include "vector3.h"

inline Vector3::Vector3()
    : x(0.0f), y(0.0f), z(0.0f)
{}

inline Vector3::Vector3(float f)
    : x(f), y(f), z(f)
{}

inline Vector3::Vector3(double d)
{
    x = y = z = (float)d;
}

inline Vector3::Vector3(int i)
{
    x = y = z = (float)i;
}

inline Vector3::Vector3(float f0, float f1, float f2)
    : x(f0), y(f1), z(f2)
{}

inline Vector3::Vector3(double d0, double d1, double d2)
    : x(float(d0)), y(float(d1)), z(float(d2))
{}

inline Vector3::Vector3(int i0, int i1, int i2)
    : x(float(i0)), y(float(i1)), z(float(i2))
{}

inline Vector3::Vector3(const Vector3& other)
    : x(other.x), y(other.y), z(other.z)
{}

inline Vector3& Vector3::operator=(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}