#include "Vector2.hpp"
#include "Vector2Int.hpp"

Vector2 Vector2i::ToVector2() {

    return Vector2((float)X, (float)Y);
}

std::string Vector2::ToString() {

    return "Vector2(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}

std::string Vector2i::ToString() {

    return "Vector2i(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}