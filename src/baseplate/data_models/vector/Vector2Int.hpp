#pragma once

#include <string>
#include <cmath>

struct Vector2;

struct Vector2i {

    int X, Y;

    Vector2i(int x, int y) : X(x), Y(y) {}
    Vector2i(int value) : X(value), Y(value) {}

    // + / +=

    Vector2i operator + (const Vector2i& other) const {

        return Vector2i(X + other.X, Y + other.Y);
    }

    Vector2i operator += (const Vector2i& other) {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    // - / -=

    Vector2i operator - (const Vector2i other) const {

        return Vector2i(X - other.X, Y - other.Y);
    }

    Vector2i operator -= (const Vector2i other) {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    // * / *=

    Vector2i operator * (const Vector2i other) const {

        return Vector2i(X * other.X, Y * other.X);
    }

    Vector2i operator * (const int value) const {

        return Vector2i(X * value, Y * value);
    }

    Vector2i operator *= (const Vector2i other) {
        X *= other.X;
        Y *= other.Y;
        return *this;
    }

    // / / //=

    Vector2i operator / (const Vector2i other) const {

        return Vector2i(X / other.X, Y / other.X);
    }

    Vector2i operator / (const int value) const {

        return Vector2i(X / value, Y / value);
    }

    Vector2i operator /= (const Vector2i other) {
        X /= other.X;
        Y /= other.Y;
        return *this;
    }

    // == / !=

    bool operator == (const Vector2i& other) const {

        return X == other.X && Y == other.Y;
    }

    bool operator != (const Vector2i& other) const {

        return !(*this == other);
    }

    // < / >

    bool operator < (const Vector2i& other) const {

        if (X != other.X) return X < other.X;
        else return Y < other.Y;
    }

    bool operator > (const Vector2i& other) const {

        if (X != other.X) return X > other.X;
        else return Y > other.Y;
    }

    // Metodos

    Vector2 ToVector2();
    std::string ToString();
};