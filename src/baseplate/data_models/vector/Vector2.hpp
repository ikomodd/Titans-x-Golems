#pragma once

#include <string>
#include <cmath>

namespace baseplate {

    struct Vector2i;

    // Vector2 ----------------------------------

    struct Vector2 {
    private:

        float m_eps = 0.01;

    public:

        float X, Y;

        Vector2(float x, float y) : X(x), Y(y) {}

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

            return Vector2(X * other.X, Y * other.Y);
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

            return (std::abs(X - other.X) < m_eps && std::abs(Y - other.Y) < m_eps);
        }

        bool operator != (const Vector2& other) const {

            return !(*this == other);
        }

        // Metodos

        Vector2i ToVector2i();
        std::string ToString();

        float LengthSquared() const {

            return X * X + Y * Y;
        }

        float Length() const {

            return std::sqrtf(X * X + Y * Y);
        }

        Vector2 Normalize() const {

            float distance = Length();

            if (distance == 0.0f) return 0;
            return Vector2(X / distance, Y / distance);
        }

        Vector2 Sign() {

            X = (X > 0) - (X < 0);
            Y = (Y > 0) - (Y < 0);

            return *this;
        }
    };

    // Vector2i -----------------------------------------

    struct Vector2i {

        int X, Y;

        Vector2i(int value = 0) : X(value), Y(value) {}
        Vector2i(int x, int y) : X(x), Y(y) {}

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

        int LengthSquared() const {

            return X * X + Y * Y;
        }
    };

    // Conversões Vector2 ----------------------------------------------------

    inline Vector2i Vector2::ToVector2i() {

        return Vector2i((int)X, (int)Y);
    }

    inline std::string Vector2::ToString() {

        return "Vector2(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
    }

    // Conversões Vector2i ----------------------------------------------------

    inline std::string Vector2i::ToString() {

        return "Vector2i(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
    }

    inline Vector2 Vector2i::ToVector2() {

        return Vector2((float)X, (float)Y);
    }
}