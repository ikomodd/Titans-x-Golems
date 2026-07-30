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

        StateManager* mStateManager = nullptr;

        float mVertices[24] = {

            0.0f, 1.0f,     0.0f, 1.0f,
            1.0f, 0.0f,     1.0f, 0.0f,
            0.0f, 0.0f,     0.0f, 0.0f,

            0.0f, 1.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 1.0f,
            1.0f, 0.0f,     1.0f, 0.0f
        };

        GLuint mVAO, mVBO;

        DisplayManager() : baseplate::Manager<DisplayManager>("display_manager") {}
        friend class baseplate::Manager<DisplayManager>;
        friend class Camera;

        baseplate::Vector2 mWindowSize = baseplate::Vector2(800.f, 600.f);

        SDL_Window* mWindow = nullptr;
        SDL_GLContext mContext = nullptr;

        glm::mat4 mProjection;

        void SetWindowSize();

    public:

        // Get

        baseplate::Vector2 GetWindowSize() {
            return mWindowSize;
        }

        glm::mat4 GetProjection() {
            return mProjection;
        }

        GLuint GetVAO() {
            return mVAO;
        }

        void _Init() override;
        void _Event(SDL_Event& event) override;
        void _Process() override;
        void _Close() override;
    };
}