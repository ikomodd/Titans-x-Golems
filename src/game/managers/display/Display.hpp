#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "baseplate/manager/Manager.hpp"

#include "baseplate/data_models/vector/Vector2.hpp"

namespace game {

    class Camera;
    class StateManager;

    class DisplayManager : public baseplate::Manager<DisplayManager> {
    private:

        StateManager* m_stateManager = nullptr;

        float m_vertices[24] = {

            0.0f, 1.0f,     0.0f, 1.0f,
            1.0f, 0.0f,     1.0f, 0.0f,
            0.0f, 0.0f,     0.0f, 0.0f,

            0.0f, 1.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 1.0f,
            1.0f, 0.0f,     1.0f, 0.0f
        };

        GLuint m_vao, m_vbo;

        DisplayManager() : baseplate::Manager<DisplayManager>("display_manager") {}
        friend class baseplate::Manager<DisplayManager>;
        friend class Camera;

        baseplate::Vector2 m_windowSize = baseplate::Vector2(800.f, 600.f);

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;

        glm::mat4 m_projection;

        void SetWindowSize();

    public:

        // Get

        baseplate::Vector2 GetWindowSize() {
            return m_windowSize;
        }

        //

        void Init() override;
        void Event(const SDL_Event& event) override;
        void Process() override;
        void Close() override;
    };
}