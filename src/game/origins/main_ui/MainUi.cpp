#include "MainUi.hpp"

#include "game/instances/frame/Frame2D.hpp"
#include "game/instances/frame/text_label/TextLabel.hpp"

void game::MainUi::Ready() {

    using Vector2 = baseplate::Vector2;

    auto* text = new TextLabel("txt", Vector2(0.5f, 0.1f), Vector2(0.2f, 0.1f), Vector2(0.5f, 0.f));
    //text->backgroundColor = baseplate::ColorPressets::RED;
    text->DefineFontAsset("geist_pixel");
    text->ChangeText("Round 1234567890");
    AddNode(text);
}