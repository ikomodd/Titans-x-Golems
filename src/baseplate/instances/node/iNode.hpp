#pragma once

#include <SDL3/SDL.h>
#include <string>

class BSPLT_iNode {
public:

    std::string Name;

    BSPLT_iNode(const char* name) : Name(name) {}
    virtual ~BSPLT_iNode() = default;

    virtual void _Ready()                      = 0;
    virtual void _Event(SDL_Event& event)      = 0;
    virtual void _Draw(SDL_Renderer* renderer) = 0;
    virtual void _Process(double delta)        = 0;
    virtual void _Close()                      = 0;
};