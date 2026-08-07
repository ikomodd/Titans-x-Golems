#pragma once

#include <iostream>

#include "baseplate/instances/node/iNode.hpp"
#include "baseplate/inheritances/children/Children.hpp"

namespace game {

    class Node : public baseplate::iNode, public baseplate::Children {
    public:

        Node(std::string name) : baseplate::iNode(name), baseplate::Children(this) {}

        void Ready()  override {}
        void Event(const SDL_Event& event) override {}
        void Draw(GLuint vao, glm::mat4 projection) override {}
        void Process(double delta)  override {}
        void Close() override {}
    };
}