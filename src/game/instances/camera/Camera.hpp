#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"

#include "game/managers/display/Display.hpp"

class GAME_Camera : public BSPLT_Node2D {
private:

    GAME_DisplayManager* m_DisplayManager = nullptr;
    bool m_MakeCurrent;

    Uint64 m_PrevDebugBufferClear = 0;
    std::vector<SDL_FRect> m_DebugBuffer = {};

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

    Vector2 GetWorldPosition(Vector2 point) {

        Vector2 WindowSize = m_DisplayManager->GetWindowSize();

        return (point - WindowSize / 2.f) / Zoom + Position;
    }

    void DrawRect(SDL_FRect rect) {

        if (SDL_GetTicks() - m_PrevDebugBufferClear > 100) {
            m_DebugBuffer.clear();
            m_PrevDebugBufferClear = SDL_GetTicks();
        }

        m_DebugBuffer.push_back(GetRectCameraView(rect));
    }

    //

    void _Ready() override {

        m_DisplayManager = &BSPLT_Manager<GAME_DisplayManager>::Get();
        
        if (m_MakeCurrent)
        m_DisplayManager->m_CurrentCamera = this;
    }

    void _Draw() override {

        for (SDL_FRect& rect : m_DebugBuffer) {

            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            //SDL_RenderFillRect(renderer, &rect);
        }
    }
};