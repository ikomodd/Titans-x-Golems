#pragma once

#include "../../instances/node/iNode.hpp"
#include "../../data_models/vector/Vector2.hpp"

namespace baseplate {

    class Transform2D {
    private:

        baseplate::Vector2 m_localPosition = 0;
        baseplate::Vector2 m_globalPosition = 0;
        
        baseplate::Vector2 m_size = 0;

    public:

        Transform2D() {}

        // Get

        Vector2 GetPosition() {

            return m_localPosition;
        }

        Vector2 GetGlobalPosition() {

            return m_globalPosition;
        }

        Vector2 GetSize() {

            return m_size;
        }

        // Set

        void SetPosition(baseplate::Vector2 position) {

            m_localPosition = position;
            // UpdateTransform();
        }

        void SetSize(baseplate::Vector2 size) {

            m_size = size;
        }

    private:

        // void UpdateTransform() {

        //     Node2D* OwnerNode = static_cast<Node2D*>(this);
        //     Node2D* OwnerParent = OwnerNode->GetParent()->As<Node2D>();

        //     if (OwnerParent) {

        //         mGlobalPosition = OwnerParent->mGlobalPosition + mLocalPosition;

        //         for (auto* child : OwnerNode->GetChildren()) {

        //             Node2D* ChildNode = child->As<Node2D>();

        //             ChildNode->UpdateTransform();
        //         }
        //     }
        // }
    };
}