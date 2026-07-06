#pragma once

#include <iostream>
#include "iNode.hpp"
#include "../../inheritances/children/Children.hpp"
#include "baseplate/data_models/vector/Vector2.hpp"

class BSPLT_Node : public BSPLT_iNode, public BSPLT_Children {
private:

    bool m_DestroyMark = false;

public:

    BSPLT_Node(const char* name) : BSPLT_iNode(name) {}
    friend class GAME_CoreManager;

    //

    template<typename T>
    T* As() {

        return dynamic_cast<T*>(this);
    }

    template<typename T>
    bool Is() {

        return dynamic_cast<T*>(this);
    }

    void Destroy() {
        m_DestroyMark = true;
    }
    //

    void _Ready()  override {}
    void _Event(SDL_Event& event) override {}
    void _Draw(SDL_Renderer* renderer) override {}
    void _Process(double delta)  override {}
    void _Close() override {}
};