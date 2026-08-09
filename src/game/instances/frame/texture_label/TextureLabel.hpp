#pragma once

#include "../Frame2D.hpp"

namespace game {

    class TextureLabel : public Frame2D {
    private:

        std::string m_textureName;

    public:

        TextureLabel(std::string name, std::string texture_name, baseplate::Vector2 position, baseplate::Vector2 size, baseplate::Vector2 anchor) : m_textureName(texture_name), Frame2D(name, position, size, anchor) {}

        void Ready() override;
        void Draw(GLuint vao, glm::mat4 projection) override;
    };
}