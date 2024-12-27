#include "../include/Camera.hpp"

Camera::Camera(Player* player, SDL_Rect* playerRect,  float zoom) {
    _following  = player;
    _zoom       = zoom;
    _playerRect = playerRect;

    // initializing Camera rect
    _camera.h   = static_cast<int>(WINDOW_HEIGHT / _zoom);
    _camera.w   = static_cast<int>(WINDOW_WIDTH / _zoom);
    _camera.x   = PLAYER_START_X - (static_cast<int>(PLAYER_WIDTH / 2) + static_cast<int>(_camera.w / 2));
    _camera.y   = PLAYER_START_Y - (static_cast<int>(PLAYER_HEIGHT / 2) + static_cast<int>(_camera.h / 2));

    // setting player initial position
    _playerRect->x = (WINDOW_WIDTH - _playerRect->w) / 2;
    _playerRect->y = (WINDOW_HEIGHT - _playerRect->h) / 2;

    // scaling player
    _playerRect->h *= _zoom;
    _playerRect->w *= _zoom;
}

void Camera::updateCamera() {
    // calculate center point of player 
    int playerCenterX = _following->getXCoordinate() + (PLAYER_WIDTH / 2);
    int playerCenterY = _following->getYCoordinate() + (PLAYER_HEIGHT / 2);

    // calculate ideal camera position to center on player
    int idealCamX = playerCenterX - (_camera.w / 2);
    int idealCamY = playerCenterY - (_camera.h / 2);

    // apply camera bounds
    _camera.x = std::max(0, std::min(WINDOW_WIDTH - _camera.w, idealCamX));
    _camera.y = std::max(0, std::min(WINDOW_HEIGHT - _camera.h, idealCamY));

    // calculate player's screen position relative to camera, accounting for zoom
    _playerRect->x = (_following->getXCoordinate() - _camera.x) * _zoom;
    _playerRect->y = (_following->getYCoordinate() - _camera.y) * _zoom;
}

void Camera::updateZoom(float zoom) {
    _zoom = zoom;

    _camera.h   = static_cast<int>(WINDOW_HEIGHT / _zoom);
    _camera.w   = static_cast<int>(WINDOW_WIDTH / _zoom);
}

SDL_Rect& Camera::getCameraRect() {
    return _camera;
}

float Camera::getZoom() {
    return _zoom;
}