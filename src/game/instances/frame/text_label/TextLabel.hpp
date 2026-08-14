#pragma once

#include "../Frame2D.hpp"

namespace game {

    class TextLabel : public Frame2D {
    private:

        std::string m_text = "";

    public:

        baseplate::Color4 textColor = baseplate::ColorPressets::WHITE;

        TextLabel(std::string name, baseplate::Vector2 position, baseplate::Vector2 size, baseplate::Vector2 anchor) : Frame2D(name, position, size, anchor) {}
    
        void ChangeText(std::string text);

        void Ready() override;
        void Draw(GLuint vao, glm::mat4 projection) override;
    };
}