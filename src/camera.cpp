#include "../include/Camera.hpp"

Camera::Camera(Player* player) {
    _following  = player;

    // Initializing Camera rect
    _camera.h   = WINDOW_HEIGHT;
    _camera.w   = WINDOW_WIDTH;
    _camera.x   = 0;
    _camera.y   = 0;
}

void Camera::updateCamera() {
    _camera.x = _following->getXCoordinate() - _camera.w / 2; // TODO: Insert Player height
    _camera.y = _following->getYCoordinate() - _camera.h / 2; // TODO: Insert Player width
}