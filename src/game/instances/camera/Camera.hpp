#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"

#include "game/managers/display/Display.hpp"

class GAME_Camera : public BSPLT_Node2D {
private:

    GAME_DisplayManager* m_DisplayManager = nullptr;
    bool m_MakeCurrent;

public:

    float Zoom;

    GAME_Camera(const char* name, Vector2 position, float zoom, bool make_current) : Zoom(zoom), m_MakeCurrent(make_current), BSPLT_Node2D(name, position, 0) {}

    SDL_FRect GetRectCameraView(SDL_FRect rect) {

        Vector2 WindowSize = m_DisplayManager->GetWindowSize();

        return SDL_FRect {

            WindowSize.X / 2 + (rect.x - Position.X) * Zoom,
            WindowSize.Y / 2 + (rect.y - Position.Y) * Zoom,
            rect.w * Zoom,
            rect.h * Zoom
        };
    }

    void _Ready() override {

        m_DisplayManager = &BSPLT_Manager<GAME_DisplayManager>::Get();
        
        if (m_MakeCurrent)
        m_DisplayManager->m_CurrentCamera = this;
    }
};