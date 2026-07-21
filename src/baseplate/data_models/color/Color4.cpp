#include "Color4.hpp"
#include "Color4Float.hpp"

Color4f Color4::Normalize() {

    return Color4f((float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
}