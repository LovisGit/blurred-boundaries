#include "../include/Player.hpp"

Player::Player(const int xCoordinate, const int yCoordinate, const int playerWidth, const int playerHeight, 
               const int picturesPerAnimation, const int walkingDistance, const int cellOnMap) 
                : 
                _xCoordinate(xCoordinate), _yCoordinate(yCoordinate), _playerWidth(playerWidth), _playerHeight(playerHeight),
                _picturesPerAnimation(picturesPerAnimation), _walkingDistance(walkingDistance), 
                _animationCounter(0), _playerPicture(0), _walkingDirection(0), _keysDown({false}), _cellOnMap(cellOnMap) {}

int Player::getXCoordinate() const {
    return _xCoordinate;
}

int Player::getYCoordinate() const {
    return _yCoordinate;
}

int Player::getPlayerPicture() const {
    return _playerPicture;
}

void Player::nextAnimationCounter() {   
    _animationCounter++;

    //when _animationCounter >= _picturesPerAnimation is true then _animationCounter = 0
    _animationCounter %= _picturesPerAnimation;
}

void Player::walkAndAnimate(const int direction, const bool keyPressed) {
    if(direction == _walkingDirection) {
        nextAnimationCounter();
    } else {
        _animationCounter = 0;
    }
        
    if(direction != -1) {
        // sets oder resets the information that a key is pressed
        _keysDown[direction] = keyPressed;
    }


    // key lifted
    if(!keyPressed) {
        _animationCounter = 0;
    }

    std::cout << "Direction: " << direction << ", KeyPressed: " << keyPressed << std::endl;
    std::cout << "KeysDown: [" << _keysDown[0] << ", " << _keysDown[1] << ", " 
              << _keysDown[2] << ", " << _keysDown[3] << "]" << std::endl;

    // changes the coordinates and the playerimage
    if(_keysDown[0]) { // up
        _playerPicture = (2 * _picturesPerAnimation) + _animationCounter;
        _yCoordinate -= _walkingDistance;
    }
    if(_keysDown[1]) { // left
        _playerPicture = (3 * _picturesPerAnimation) + _animationCounter;
        _xCoordinate -= _walkingDistance;
    }
    if(_keysDown[2]) { // down
        _playerPicture = (0 * _picturesPerAnimation) + _animationCounter;
        _yCoordinate += _walkingDistance;
    }
    if(_keysDown[3]) { // right
        _playerPicture = (1 * _picturesPerAnimation) + _animationCounter;
        _xCoordinate += _walkingDistance;
    }

    _walkingDirection = direction;
}