#include "../include/Player.hpp"

Player::Player(const int xCoordinate, const int yCoordinate, const int picturesPerAnimation, const int walkingDistance) : 
        _xCoordinate(xCoordinate), _yCoordinate(yCoordinate), _picturesPerAnimation(picturesPerAnimation), 
        _walkingDistance(walkingDistance), _animationCounter(0), _playerPicture(0), _walkingDirection(0), _keysDown({0}) {}

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

/*
void Player::printKeysDown() const{
    std::cout << "_keysDown: ";
    for(auto& i : _keysDown) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}
*/

void Player::walkAndAnimate(const int direction, const bool keyPressed) {
    if(direction == _walkingDirection) {
        nextAnimationCounter();
    } else {
        _animationCounter = 0;
    }
    
    // sets oder resets the information that a key is pressed
    _keysDown[direction] = keyPressed;

    //printKeysDown();

    // key lifted
    if(!keyPressed) {
        _animationCounter = 0;
    }

    // changes the coordinates and the playerimage
    if(_keysDown[0]) {
        _playerPicture = (3 * _picturesPerAnimation) + _animationCounter;
        _yCoordinate -= _walkingDistance;
    }
    if(_keysDown[1]) {
        _playerPicture = (1 * _picturesPerAnimation) + _animationCounter;
        _xCoordinate -= _walkingDistance;
    }
    if(_keysDown[2]) {
        _playerPicture = (0 * _picturesPerAnimation) + _animationCounter;
        _yCoordinate += _walkingDistance;
    }
    if(_keysDown[3]) {
        _playerPicture = (2 * _picturesPerAnimation) + _animationCounter;
        _xCoordinate += _walkingDistance;
    }

    _walkingDirection = direction;
}