#include "MainUi.hpp"

#include "game/instances/frame/Frame2D.hpp"

void game::MainUi::Ready() {

    using Vector2 = baseplate::Vector2;

    auto* frame = new Frame2D("test", Vector2(0.5f, 0.1f), Vector2(0.2f, 0.1f), Vector2(0.5f, 0.f));
    frame->backgroundColor = baseplate::ColorPressets::WHITE;
    AddNode(frame);
}