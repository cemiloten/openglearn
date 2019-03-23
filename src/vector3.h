#pragma once

class Vector3
{
public:
    union {
        struct { float x, y, z; };
        struct { float r, g, b; };
        float e[3];
    };

    inline Vector3();
    inline Vector3(float  f);
    inline Vector3(float  f0, float  f1, float  f2);
    inline Vector3(double d);
    inline Vector3(double d0, double d1, double d2);
    inline Vector3(int    i);
    inline Vector3(int    i0, int    i1, int    i2);

    inline Vector3(const Vector3& v);
    inline Vector3& operator=(const Vector3& v);

    // inline const Vector3& operator + () const { return *this; }
    // inline Vector3 operator - () const { return Vector3(-x, -y, -z); }
    // inline double operator [] (int index) const { return e[index]; }
    // inline double& operator [] (int index) { return e[index]; };

    // inline Vector3& operator += (const Vector3& v2);
    // inline Vector3& operator -= (const Vector3& v2);
    // inline Vector3& operator *= (const Vector3& v2);
    // inline Vector3& operator /= (const Vector3& v2);
    // inline Vector3& operator *= (const double t);
    // inline Vector3& operator /= (const double t);

    // inline double length() const {
    //     return sqrt(x*x + y*y + z*z);
    // }

    // inline double squared_length() const {
    //     return x*x + y*y + z*z;
    // }

    // inline void make_unit_vector() {
    //     double k = 1.0f / length();
    //     *this *= k;
    // }

    //  inline Vector3 normalized() {
    //      double k = 1.0f / length();
    //      return Vector3(x * k, y * k, z * k);
    //  }
};

// inline std::istream& operator >> (std::istream& is, Vec3& v) {
//     is >> v.x >> v.y >> v.z;
//     return is;
// }

// inline std::ostream& operator << (std::ostream& os, const Vec3& v) {
//     os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
//     return os;
// }

// inline Vec3 operator + (const Vec3& v1, const Vec3& v2) {
//     return Vec3(
//         v1.x + v2.x,
//         v1.y + v2.y,
//         v1.z + v2.z);
// }

// inline Vec3 operator - (const Vec3& v1, const Vec3& v2) {
//     return Vec3(
//         v1.x - v2.x,
//         v1.y - v2.y,
//         v1.z - v2.z);
// }

// inline Vec3 operator * (const Vec3& v1, const Vec3& v2) {
//     return Vec3(
//         v1.x * v2.x,
//         v1.y * v2.y,
//         v1.z * v2.z);
// }

// inline Vec3 operator / (const Vec3& v1, const Vec3& v2) {
//     return Vec3(
//         v1.x / v2.x,
//         v1.y / v2.y,
//         v1.z / v2.z);
// }

// inline Vec3 operator * (double t, const Vec3& v) {
//     return Vec3(t * v.x, t * v.y, t * v.z);
// }

// inline Vec3 operator * (const Vec3& v, double t) {
//     return Vec3(t * v.x, t * v.y, t * v.z);
// }

// inline Vec3 operator / (const Vec3& v, double t) {
//     return Vec3(v.x / t, v.y / t, v.z / t);
// }

// inline double dot(const Vec3& v1, const Vec3& v2) {
//     return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
// }

// inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
//     return Vec3(
//          (v1.y*v2.z - v1.z*v2.y),
//         -(v1.x*v2.z - v1.z*v2.x),
//          (v1.x*v2.y - v1.y*v2.x));
// }

// inline Vec3& Vec3::operator += (const Vec3& v) {
//     x += v.x;
//     y += v.y;
//     z += v.z;
//     return *this;
// }

// inline Vec3& Vec3::operator -= (const Vec3& v) {
//     x -= v.x;
//     y -= v.y;
//     z -= v.z;
//     return *this;
// }

// inline Vec3& Vec3::operator *= (const Vec3& v) {
//     x *= v.x;
//     y *= v.y;
//     z *= v.z;
//     return *this;
// }

// inline Vec3& Vec3::operator /= (const Vec3& v) {
//     x /= v.x;
//     y /= v.y;
//     z /= v.z;
//     return *this;
// }

// inline Vec3& Vec3:: operator *= (const double t) {
//     x *= t;
//     y *= t;
//     z *= t;
//     return *this;
// }

// inline Vec3& Vec3:: operator /= (const double t) {
//     x /= t;
//     y /= t;
//     z /= t;
//     return *this;
// }

// inline Vec3 unit_vector(Vec3 v) {
//     return v / v.length();
// }

// }