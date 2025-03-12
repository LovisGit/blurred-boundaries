#pragma once
#include "Constants.hpp"
#include "ObjectAdminstrator.hpp"

class Player {
private:
    int _xCoordinate;
    int _yCoordinate;
    int _playerWidth;
    int _playerHeight;

    // determines how many pictures are used for one animation
    int _picturesPerAnimation;

    int _walkingDistance;
    int _animationCounter;
    int _playerPicture;
    int _walkingDirection;
    int _currentCell;

    char _name[32];
 
    // information about the keys pressed
    std::array<bool, 4> _keysDown;

    ObjectAdministrator theObjectManager;
    
    void nextAnimationCounter();
    bool checkCollisionPlayer(int direction);

public:
    Player(const int xCoordinate, const int yCoordinate, const int playerWidth, const int playerHeight, 
           const int picturesPerAnimation, const int walkingDistance);

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getPlayerPicture() const;
    char* getName();
    void setName(char name[]);

    void walkAndAnimate(const int direction, const bool keyPressed);

};