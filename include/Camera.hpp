#pragma once
#include "Player.hpp"
#include "Constants.hpp"

class Camera
{
private:
    SDL_Rect    _camera;
    float       _zoom;
    Player*     _following;

public:
    Camera(Player* player);
    ~Camera();

    void updateCamera();
};