#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>

struct Vector2D {
    float x;
    float y;

    // Constructors
    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    // Vector addition
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Vector subtraction
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // Scalar multiplication
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Length of the vector
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Distance to another vector (point)
    float distance(const Vector2D& other) const {
        return (*this - other).length();
    }

    // Normalize the vector (return unit vector)
    Vector2D normalized() const {
        float len = length();
        if (len > 0.0f) {
            return Vector2D(x / len, y / len);
        }
        return Vector2D(0.0f, 0.0f);
    }
};

#endif // VECTOR2D_HPP

#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

struct Vector2D {
    float x;
    float y;
};

#endif
