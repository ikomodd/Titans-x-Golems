#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"

namespace game {

    class HealthBar : public baseplate::Node2D {
    private:

        using Vector2 = baseplate::Vector2;

        float m_FullHealth;
        float m_CurrentHealth;

    public:

        HealthBar() : baseplate::Node2D("health_bar", 0, Vector2(2.0f, 50.0f)) {}

        void Update(float health);

        void _Ready() override;
        void _Draw(GLuint vao, glm::mat4 projection) override;
    };
}