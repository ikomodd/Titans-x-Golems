#pragma once

#include <iostream>

#include "iNode.hpp"
#include "../../inheritances/children/Children.hpp"

namespace baseplate {

    class Node : public iNode, public Children {
    public:

        Node(const char* name) : iNode(name), Children(this) {}

        void _Ready()  override {}
        void _Event(SDL_Event& event) override {}
        void _Draw() override {}
        void _Process(double delta)  override {}
        void _Close() override {}
    };
}