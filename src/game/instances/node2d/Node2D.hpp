#pragma once

#include "game/instances/node/Node.hpp"
#include "baseplate/inheritances/transform/Transform.hpp"

namespace game {

    class Node2D : public Node, public baseplate::Transform2D {
    public:

        Node2D(const char* name, baseplate::Vector2 position, baseplate::Vector2 size) : Node(name), baseplate::Transform2D() {}
    };
}