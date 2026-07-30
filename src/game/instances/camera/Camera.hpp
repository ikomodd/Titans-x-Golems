#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"

#include "game/managers/display/Display.hpp"

namespace game {

    class Camera : public baseplate::Node2D {
    private:

        DisplayManager* mDisplayManager = nullptr;
        bool mMakeCurrent;

    public:

        float Zoom;

        inline static Camera* CurrentCamera = nullptr;

        Camera(const char* name, baseplate::Vector2 position, float zoom, bool make_current) : Zoom(zoom), mMakeCurrent(make_current), baseplate::Node2D(name, position, 0) {}

        // Transforma a posição e tamanho de um node em relação à camera 

        void TransformToCameraView(baseplate::Vector2& node_position, baseplate::Vector2& node_size);

        // Transforma um ponto em relação à camera

        baseplate::Vector2 GetWorldPosition(baseplate::Vector2 point);

        //

        void _Ready() override {

            mDisplayManager = &baseplate::Manager<game::DisplayManager>::Get();
            
            if (mMakeCurrent)
                CurrentCamera = this;
        }
    };
}