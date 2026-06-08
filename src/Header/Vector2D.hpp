#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP




#include <cmath>

struct Vector2D {
    float x;
    float y;




    // constructors
    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    // addition
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // subtraction
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // multiplication
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // length
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // distance
    float distance(const Vector2D& other) const {
        return (*this - other).length();
    }

    // normalize
    Vector2D normalized() const {
        float len = length();
        if (len > 0.0f) {
            return Vector2D(x / len, y / len);
        }
        return Vector2D(0.0f, 0.0f);
    }
};

#endif
