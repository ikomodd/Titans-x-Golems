#pragma once

#include <iostream>

#include "iNode.hpp"
#include "../../inheritances/children/Children.hpp"

namespace baseplate {

    class Node : public iNode, public Children {
    public:

        Node(std::string name) : iNode(name), Children(this) {}

        void Ready()  override {}
        void Event(const SDL_Event& event) override {}
        void Draw(GLuint vao, glm::mat4 projection) override {}
        void Process(double delta)  override {}
        void Close() override {}
    };
}