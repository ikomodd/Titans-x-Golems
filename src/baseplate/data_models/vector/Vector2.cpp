#include "Vector2.hpp"
#include "Vector2Int.hpp"



std::string Vector2::ToString() {

    return "Vector2(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}

Vector2i Vector2::ToVector2i() {

    return Vector2i((int)X, (int)Y);
}

//

std::string Vector2i::ToString() {

    return "Vector2i(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}

Vector2 Vector2i::ToVector2() {

    return Vector2((float)X, (float)Y);
}