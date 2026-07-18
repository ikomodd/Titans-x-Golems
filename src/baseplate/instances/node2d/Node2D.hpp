#pragma once

#include "../node/Node.hpp"
#include "../../inheritances/transform/Transform.hpp"

class BSPLT_Node2D : public BSPLT_Node, public BSPLT_Transform2D {
public:

    BSPLT_Node2D(const char* name, Vector2 position, Vector2 size) : BSPLT_Node(name), BSPLT_Transform2D() {}
};