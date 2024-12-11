#pragma once
#include <iostream>

class Player {

private:
    int _xCoordinate;
    int _yCoordinate;
    int _picturesPerAnimation;
    int _walkingDistance;
    int _animationCounter;
    int _playerPicture;
    char _walkingDirection;

    void nextAnimationCounter();

public:
    Player(const int xCoordinate, const int yCoordinate, const int picturesPerAnimation, const int walkingDistance);

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getPlayerPicture() const;

    void walkAndAnimate(const char direction);

};