#pragma once

#include "game/instances/node2d/Node2D.hpp"

#include "game/managers/display/Display.hpp"

namespace game {

    class Camera : public Node2D {
    private:

        DisplayManager* m_displayManager = nullptr;
        bool m_makeCurrent;

    public:

        float zoom;

        inline static Camera* currentCamera = nullptr;

        Camera(const char* name, baseplate::Vector2 position, float zoom, bool make_current) : zoom(zoom), m_makeCurrent(make_current), Node2D(name, position, 0) {}

        // Transforma a posição e tamanho de um node em relação à camera 

        void TransformToCameraView(baseplate::Vector2& node_position, baseplate::Vector2& node_size);

        // Transforma um ponto em relação à camera

        baseplate::Vector2 GetWorldPosition(baseplate::Vector2 point);

        //

        void Ready() override {

            m_displayManager = &baseplate::Manager<game::DisplayManager>::Get();
            
            if (m_makeCurrent)
                currentCamera = this;
        }
    };
}