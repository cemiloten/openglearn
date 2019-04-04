#pragma once

struct Vector3 {
public:
    float x, y, z;

    Vector3()
        : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(float f)
        : x(f), y(f), z(f) {}

    Vector3(float xx, float yy, float zz)
        : x(xx), y(yy), z(zz) {}

};