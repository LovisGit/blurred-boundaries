#pragma once
#include <array>
#include <iostream>

class Player {

private:
    int _xCoordinate;
    int _yCoordinate;
    int _picturesPerAnimation;
    int _walkingDistance;
    int _animationCounter;
    int _playerPicture;
    int _walkingDirection;
    std::array<bool, 4> _keysDown;

    void nextAnimationCounter();

    //void printKeysDown();

public:
    Player(const int xCoordinate, const int yCoordinate, const int picturesPerAnimation, const int walkingDistance);

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getPlayerPicture() const;

    void walkAndAnimate(const int direction, const bool keyPressed);

};