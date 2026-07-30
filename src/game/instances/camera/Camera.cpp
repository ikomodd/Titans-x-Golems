#include "Camera.hpp"

void game::Camera::TransformToCameraView(baseplate::Vector2& node_position, baseplate::Vector2& node_size) {
    baseplate::Vector2 WindowSize = mDisplayManager->GetWindowSize();

    node_position = baseplate::Vector2(WindowSize.X / 2 + (node_position.X - GetPosition().X) * Zoom, WindowSize.Y / 2 + (node_position.Y - GetPosition().Y) * Zoom);
    node_size = baseplate::Vector2(node_size.X * Zoom, node_size.Y * Zoom);
}

baseplate::Vector2 game::Camera::GetWorldPosition(baseplate::Vector2 point) {

    baseplate::Vector2 WindowSize = mDisplayManager->GetWindowSize();

    return (point - WindowSize / 2.f) / Zoom + GetPosition();
}