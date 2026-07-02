#pragma once

#include <SDL3/SDL.h>

#include "baseplate/manager/Manager.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"

class GAME_Camera;

class GAME_DisplayManager : public BSPLT_Manager<GAME_DisplayManager> {
private:

    GAME_DisplayManager() : BSPLT_Manager<GAME_DisplayManager>("display_manager") {}
    friend class BSPLT_Manager<GAME_DisplayManager>;
    friend class GAME_Camera;

    GAME_Camera* m_CurrentCamera = nullptr;

    Vector2 m_WindowSize = Vector2(320.f, 180.f);

public:

    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

    GAME_Camera* GetCurrentCamera() {
        return m_CurrentCamera;
    }

    Vector2 GetWindowSize() {
        return m_WindowSize;
    }

private:

    void SetWindowSize();

public:

    void _Init() override;
    void _Event(SDL_Event& event) override;
    void _Process() override;
    void _Close() override;
};