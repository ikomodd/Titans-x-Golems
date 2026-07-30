#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "baseplate/manager/Manager.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"

class GAME_Camera;

class GAME_DisplayManager : public baseplate::Manager<GAME_DisplayManager> {
private:

    float m_Vertices[24] = {

        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f,
        0.0f, 0.0f,     0.0f, 0.0f,

        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f
    };

    GLuint VAO, VBO;

    GAME_DisplayManager() : baseplate::Manager<GAME_DisplayManager>("display_manager") {}
    friend class baseplate::Manager<GAME_DisplayManager>;
    friend class GAME_Camera;

    baseplate::Vector2 m_WindowSize = baseplate::Vector2(800.f, 600.f);

    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_Context = nullptr;

    glm::mat4 m_Projection;

public:

    baseplate::Vector2 GetWindowSize() {
        return m_WindowSize;
    }

    glm::mat4 GetProjection() {

        return m_Projection;
    }

    GLuint GetVAO() {

        return VAO;
    }

private:

    void SetWindowSize();

public:

    void _Init() override;
    void _Event(SDL_Event& event) override;
    void _Process() override;
    void _Close() override;
};