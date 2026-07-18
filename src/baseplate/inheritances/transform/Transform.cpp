#include "Transform.hpp"

#include "../../instances/node2d/Node2D.hpp"

// SET

void BSPLT_Transform2D::SetPosition(Vector2 position) {

    m_LocalPosition = position;
    UpdateTransform();
}

void BSPLT_Transform2D::SetSize(Vector2 size) {

    m_Size = size;
}

//

void BSPLT_Transform2D::UpdateTransform() {

    BSPLT_Node2D* OwnerNode = static_cast<BSPLT_Node2D*>(this);
    BSPLT_Node2D* OwnerParent = OwnerNode->GetParent()->As<BSPLT_Node2D>();

    if (OwnerParent) {

        m_GlobalPosition = OwnerParent->m_GlobalPosition + m_LocalPosition;

        for (auto* child : OwnerNode->GetChildren()) {

            BSPLT_Node2D* ChildNode = static_cast<BSPLT_Node2D*>(child);

            ChildNode->UpdateTransform();
        }
    }
}