#include "MainUi.hpp"

#include "game/instances/frame/Frame2D.hpp"
#include "game/instances/frame/text_label/TextLabel.hpp"

void game::MainUi::Ready() {

    using Vector2 = baseplate::Vector2;

    auto* roundDisplay = new TextLabel("round_display", Vector2(0.5f, 0.1f), Vector2(0.2f, 0.1f), Vector2(0.5f, 0.f));
    roundDisplay->DefineFontAsset("geist_pixel");
    roundDisplay->ChangeText("Round 1");
    AddNode(roundDisplay);
}