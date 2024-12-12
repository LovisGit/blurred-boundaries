#include "../include/Player.hpp"

Player::Player(const int xCoordinate, const int yCoordinate, const int picturesPerAnimation, const int walkingDistance) : 
        _xCoordinate(xCoordinate), _yCoordinate(yCoordinate), _picturesPerAnimation(picturesPerAnimation), 
        _walkingDistance(walkingDistance), _animationCounter(0), _playerPicture(0), _walkingDirection('0') {
    initKeysDown();
}

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
    _animationCounter %= _picturesPerAnimation;     //when _animationCounter >= _picturesPerAnimation is true then _animationCounter = 0
}

void Player::walkAndAnimate(const char direction) {
    if(direction == _walkingDirection) {
        nextAnimationCounter();
    } else {
        _animationCounter = 0;
    }

    switch (direction) {
        case '0':
            //not in use
            break;
        case 'W':
            _playerPicture = (3 * _picturesPerAnimation) + _animationCounter;
            _yCoordinate -= _walkingDistance;
            break;
        case 'A':
            _playerPicture = (1 * _picturesPerAnimation) + _animationCounter;
            _xCoordinate -= _walkingDistance;
            break;
        case 'S':
            _playerPicture = (0 * _picturesPerAnimation) + _animationCounter;
            _yCoordinate += _walkingDistance;
            break;
        case 'D':
            _playerPicture = (2 * _picturesPerAnimation) + _animationCounter;
            _xCoordinate += _walkingDistance;
            break;
        default:
            break;
    }
    _walkingDirection = direction;
}

/*
void Player::printKeysDown() {
    std::cout << "_keysDown: ";
    for(int i = 0; i < 4; i++) {
        std::cout << _keysDown[i] << ", ";
    }
    std::cout << std::endl;
}
*/

void Player::initKeysDown() {
    for(size_t i = 0; i < _keysDown.size(); i++) {
        _keysDown[i] = false;
    }
}

void Player::walkAndAnimate2(const int direction, const bool keyPressed) {
    if(direction == _walkingDirection2) {
        nextAnimationCounter();
    } else {
        _animationCounter = 0;
    }
    
    _keysDown[direction] = keyPressed;

    //printKeysDown();

    if(!keyPressed) {
        _animationCounter = 0;
    }

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

    _walkingDirection2 = direction;
}