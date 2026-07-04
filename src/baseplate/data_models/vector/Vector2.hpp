#pragma once

#include <string>
#include <cmath>

struct Vector2 {
private:

    float Eps = 0.01;

public:

    float X, Y;

    Vector2(float x = 0, float y = 0) : X(x), Y(y) {}

    Vector2(float value = 0.0f) : X(value), Y(value) {}
    Vector2(int value = 0) : X(value), Y(value) {}

    // + / +=

    Vector2 operator + (const Vector2& other) const {

        return Vector2(X + other.X, Y + other.Y);
    }

    Vector2 operator += (const Vector2& other) {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    // - / -=

    Vector2 operator - (const Vector2 other) const {

        return Vector2(X - other.X, Y - other.Y);
    }

    Vector2 operator -= (const Vector2 other) {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    // * / *=

    Vector2 operator * (const Vector2 other) const {

        return Vector2(X * other.X, Y * other.X);
    }

    Vector2 operator * (const float value) const {

        return Vector2(X * value, Y * value);
    }

    Vector2 operator *= (const Vector2 other) {
        X *= other.X;
        Y *= other.Y;
        return *this;
    }

    // / / //=

    Vector2 operator / (const Vector2 other) const {

        return Vector2(X / other.X, Y / other.X);
    }

    Vector2 operator / (const float value) const {

        return Vector2(X / value, Y / value);
    }

    Vector2 operator /= (const Vector2 other) {
        X /= other.X;
        Y /= other.Y;
        return *this;
    }

    // == / !=

    bool operator == (const Vector2& other) const {

        return (std::abs(X - other.X) < Eps && std::abs(Y - other.Y) < Eps);
    }

    bool operator != (const Vector2& other) const {

        return !(*this == other);
    }

    // Metodos

    std::string ToString();
};