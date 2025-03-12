#pragma once
#include "Player.hpp"
#include "Constants.hpp"

class Camera {
private:
    float                   _zoom;
    SDL_Rect                _camera;
    Player*                 _following;
    SDL_Rect*               _playerRect; 

public:
    Camera(float zoom, Player* player, SDL_Rect* playerRect);

    void                    updateCamera(SDL_Rect& shadowRect);
    void                    setZoom(float zoom);
    SDL_Rect&               getCameraRect();
    float                   getZoom() const;
};