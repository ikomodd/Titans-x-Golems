#pragma once

#include "../node/Node.hpp"
#include "../../inheritances/transform/Transform.hpp"

namespace baseplate {

    class Node2D : public Node, public Transform2D {
    public:

        Node2D(const char* name, baseplate::Vector2 position, baseplate::Vector2 size) : Node(name), Transform2D() {}
    };
}