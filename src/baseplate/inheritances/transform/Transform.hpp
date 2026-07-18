#pragma once

#include "../../data_models/vector/Vector2.hpp"

class BSPLT_Node;

class BSPLT_Transform2D {
private:

    Vector2 m_LocalPosition = 0;
    Vector2 m_GlobalPosition = 0;
    
    Vector2 m_Size = 0;

public:

    BSPLT_Transform2D() {}

    // Get

    Vector2 GetPosition() {

        return m_LocalPosition;
    }

    Vector2 GetGlobalPosition() {

        return m_GlobalPosition;
    }

    Vector2 GetSize() {

        return m_Size;
    }

    // Set

    void SetPosition(Vector2 position);
    void SetSize(Vector2 size);

private:

    void UpdateTransform();
};