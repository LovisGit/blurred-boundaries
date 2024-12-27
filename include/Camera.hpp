#pragma once
#include "Player.hpp"
#include "Constants.hpp"

class Camera {
private:
    SDL_Rect                _camera;
    float                   _zoom;
    Player*                 _following;
    SDL_Rect*               _playerRect;

public:
    Camera(Player* player, SDL_Rect* playerRect,  float zoom);

    void                    updateCamera();
    void                    updateZoom(float zoom);
    SDL_Rect&               getCameraRect();
    float                   getZoom();
};