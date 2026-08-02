#include "Camera.hpp"

void game::Camera::TransformToCameraView(baseplate::Vector2& node_position, baseplate::Vector2& node_size) {
    baseplate::Vector2 windowSize = m_displayManager->GetWindowSize();

    node_position = baseplate::Vector2(windowSize.X / 2 + (node_position.X - GetPosition().X) * zoom, windowSize.Y / 2 + (node_position.Y - GetPosition().Y) * zoom);
    node_size = baseplate::Vector2(node_size.X * zoom, node_size.Y * zoom);
}

baseplate::Vector2 game::Camera::GetWorldPosition(baseplate::Vector2 point) {

    baseplate::Vector2 windowSize = m_displayManager->GetWindowSize();

    return (point - windowSize / 2.f) / zoom + GetPosition();
}