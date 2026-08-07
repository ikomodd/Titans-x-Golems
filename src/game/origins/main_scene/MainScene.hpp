#pragma once

#include "../Origin.hpp"

namespace game {

    class MainScene : public Origin {
    public:

        MainScene() : Origin("main_scene") {}

        void Ready() override;
    };
}