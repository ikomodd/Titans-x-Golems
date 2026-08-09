#pragma once

#include "../../data_models/vector/Vector2.hpp"
#include "../../instances/node/iNode.hpp"

namespace baseplate {

    class UiTransform {
    private:
        
        Vector2 m_position = 0;
        Vector2 m_size = 0;

    public:

        Vector2 positionAnchor = 0;
        Vector2 localPosition = 0;
        Vector2 localSize = 0;

        UiTransform() {}
        virtual ~UiTransform() {}

        // Get

        Vector2 GetPosition() {

            return m_position;
        }

        Vector2 GetSize() {

            return m_size;
        }

        //

        void UpdateTransform(Vector2 window_size) {

            auto* nodeOwner = dynamic_cast<iNode*>(this);

            if (nodeOwner->GetParent() == nullptr) {

                m_size = window_size * localSize;
                m_position = (localPosition * window_size) - positionAnchor * m_size;
            }
            else {


            }
        }
    };
}