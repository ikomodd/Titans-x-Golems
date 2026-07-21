#pragma once

#include "baseplate/instances/node2d/Node2D.hpp"

class GAME_HealthBar : public BSPLT_Node2D {
private:

    float m_FullHealth;
    float m_CurrentHealth;

public:

    void Update(float health);

    void _Ready() override;
    void _Draw() override;
};