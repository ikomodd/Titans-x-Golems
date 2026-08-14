#pragma once

#include "../../data_models/vector/Vector2.hpp"
#include "../../instances/node/iNode.hpp"

#include "../asset_data/AssetData.hpp"

#include <algorithm>

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

            auto* ownerAssetData = dynamic_cast<AssetData*>(nodeOwner);
            auto* parentTransform = dynamic_cast<UiTransform*>(nodeOwner->GetParent());

            if (!parentTransform) {

                if (ownerAssetData && ownerAssetData->HasTexture()) {
                    float pivot = std::min(window_size.X, window_size.Y);

                    m_size = localSize * pivot;
                    m_position = (localPosition * window_size) - positionAnchor * m_size;
                }
                else {

                    m_size = localSize * window_size;
                    m_position = (localPosition * window_size) - positionAnchor * m_size;
                }
            }
        }
    };
}