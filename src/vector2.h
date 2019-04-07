#pragma once

struct Vector2 {
  public:
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}

    Vector2(float f) : x(f), y(f) {}

    Vector2(float xx, float yy) : x(xx), y(yy) {}
};