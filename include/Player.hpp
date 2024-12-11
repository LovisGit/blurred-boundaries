#pragma once
#include <iostream>

class Player {

private:
    char _lookingDirection; //noch nicht benötigt
    char _walkingDirection;
    int _xCoordinate;
    int _yCoordinate;
    int _playerPicture;
    int _picturesPerAnimation;
    int _animationCounter;
    int _walkingDistance;

    void nextAnimationCounter();

public:
    Player(const int xCoordinate, const int yCoordinate, const int picturesPerAnimation, const int walkingDistance);

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getPlayerPicture() const;

    void walkAndAnimate(const char direction);

};