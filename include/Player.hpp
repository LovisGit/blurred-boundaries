#pragma once
#include "Constants.hpp"
#include "ObjectAdminstrator.hpp"

class Player {

private:
    int _xCoordinate;
    int _yCoordinate;
    int _playerWidth;
    int _playerHeight;
    int _picturesPerAnimation;
    int _walkingDistance;
    int _animationCounter;
    int _playerPicture;
    int _walkingDirection;
    int _currentCell;
    std::array<bool, 4> _keysDown;

    ObjectAdministrator theObjectAdministrator;

    void nextAnimationCounter();

public:
    Player(const int xCoordinate, const int yCoordinate, const int playerWidth, const int playerHeight, 
           const int picturesPerAnimation, const int walkingDistance);

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getPlayerPicture() const;

    void walkAndAnimate(const int direction, const bool keyPressed);

};