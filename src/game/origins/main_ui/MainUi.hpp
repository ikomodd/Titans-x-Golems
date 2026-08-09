#pragma once

#include "../Origin.hpp"

namespace game {

    class MainUi : public Origin {
    public:

        MainUi() : Origin("main_ui") {};

        void Ready() override;
    };
}