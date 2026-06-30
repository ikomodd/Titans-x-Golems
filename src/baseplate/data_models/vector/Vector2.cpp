#include "Vector2.hpp"
#include "Vector2Int.hpp"

Vector2 Vector2i::ToVector2() {

    return Vector2((float)X, (float)Y);
}