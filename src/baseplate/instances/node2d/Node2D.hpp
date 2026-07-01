#pragma once

#include "../node/Node.hpp"
#include "../../data_models/vector/Vector2.hpp"

class BSPLT_Node2D : public BSPLT_Node {
public:

    Vector2 Position;
    Vector2 Size;

    BSPLT_Node2D(const char* name, Vector2 position, Vector2 size) : Position(position), Size(size), BSPLT_Node(name) {}
};