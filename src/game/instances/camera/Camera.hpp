#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"

#include "game/managers/display/Display.hpp"

class GAME_Camera : public baseplate::Node2D {
private:

    GAME_DisplayManager* m_DisplayManager = nullptr;
    bool m_MakeCurrent;

    Uint64 m_PrevDebugBufferClear = 0;
    std::vector<SDL_FRect> m_DebugBuffer = {};

public:

    float Zoom;

    inline static GAME_Camera* CurrentCamera = nullptr;

    GAME_Camera(const char* name, baseplate::Vector2 position, float zoom, bool make_current) : Zoom(zoom), m_MakeCurrent(make_current), baseplate::Node2D(name, position, 0) {}

    void TransformToCameraView(baseplate::Vector2& node_position, baseplate::Vector2& node_size) {
        baseplate::Vector2 WindowSize = m_DisplayManager->GetWindowSize();

        node_position = baseplate::Vector2(WindowSize.X / 2 + (node_position.X - GetPosition().X) * Zoom, WindowSize.Y / 2 + (node_position.Y - GetPosition().Y) * Zoom);
        node_size = baseplate::Vector2(node_size.X * Zoom, node_size.Y * Zoom);
    }

    baseplate::Vector2 GetWorldPosition(baseplate::Vector2 point) {

        baseplate::Vector2 WindowSize = m_DisplayManager->GetWindowSize();

        return (point - WindowSize / 2.f) / Zoom + GetPosition();
    }

    void DrawRect(SDL_FRect rect) {

        // if (SDL_GetTicks() - m_PrevDebugBufferClear > 100) {
        //     m_DebugBuffer.clear();
        //     m_PrevDebugBufferClear = SDL_GetTicks();
        // }

        // m_DebugBuffer.push_back(GetRectCameraView(rect));
    }

    //

    void _Ready() override {

        m_DisplayManager = &baseplate::Manager<GAME_DisplayManager>::Get();
        
        if (m_MakeCurrent)
            CurrentCamera = this;
    }

    void _Draw() override {

        for (SDL_FRect& rect : m_DebugBuffer) {

            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            //SDL_RenderFillRect(renderer, &rect);
        }
    }
};