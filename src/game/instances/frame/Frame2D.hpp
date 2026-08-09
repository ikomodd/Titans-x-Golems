#pragma once

#include "game/instances/node/Node.hpp"

#include "baseplate/inheritances/ui_transform/UiTransform.hpp"
#include "baseplate/inheritances/asset_data/AssetData.hpp"

namespace game {

    class Frame2D : public Node, public baseplate::AssetData, public baseplate::UiTransform {
    public:

        Frame2D(std::string name, baseplate::Vector2 position, baseplate::Vector2 size, baseplate::Vector2 anchor);
    
        void Ready() override;
        void Draw(GLuint vao, glm::mat4 projection) override;
    };
}