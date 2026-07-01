#pragma once

#include <iostream>
#include "iNode.hpp"
#include "../../inheritances/children/Children.hpp"
#include "baseplate/data_models/vector/Vector2.hpp"

class BSPLT_Node : public BSPLT_iNode, public BSPLT_Children {
public:

    BSPLT_Node(const char* name) : BSPLT_iNode(name) {}

    void _Ready()  override {}
    void _Event(SDL_Event& event) override {}
    void _Draw(SDL_Renderer* renderer, float viewport_scale) override {}
    void _Process(double delta)  override {}
    void _Close() override {}
};