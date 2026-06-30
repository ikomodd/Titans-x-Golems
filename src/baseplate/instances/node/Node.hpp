#pragma once

#include <iostream>
#include "iNode.hpp"
#include "../../inheritances/children/Children.hpp"

class BSPLT_Node : public BSPLT_iNode, public BSPLT_Children {
public:

    BSPLT_Node(const char* name) : BSPLT_iNode(name) {}

    void _Ready()  override {}
    void _Event(SDL_Event& event) override {}
    void _Draw(SDL_Renderer* renderer) override {}
    void _Process(double delta)  override {}
    void _Close() override {}
};