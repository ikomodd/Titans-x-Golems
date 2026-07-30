#pragma once

#include "../../instances/node/iNode.hpp"
#include "../../data_models/vector/Vector2.hpp"

namespace baseplate {

    class Transform2D {
    private:

        baseplate::Vector2 mLocalPosition = 0;
        baseplate::Vector2 mGlobalPosition = 0;
        
        baseplate::Vector2 mSize = 0;

    public:

        Transform2D() {}

        // Get

        Vector2 GetPosition() {

            return mLocalPosition;
        }

        Vector2 GetGlobalPosition() {

            return mGlobalPosition;
        }

        Vector2 GetSize() {

            return mSize;
        }

        // Set

        void SetPosition(baseplate::Vector2 position) {

            mLocalPosition = position;
            // UpdateTransform();
        }

        void SetSize(baseplate::Vector2 size) {

            mSize = size;
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