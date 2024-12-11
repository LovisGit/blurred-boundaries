#include "../include/Player.hpp"

Player::Player(const int xCoordinate, const int yCoordinate, const int picturesPerAnimation, const int walkingDistance) : 
        _xCoordinate(xCoordinate), _yCoordinate(yCoordinate), _picturesPerAnimation(picturesPerAnimation), 
        _walkingDistance(walkingDistance), _animationCounter(0), _playerPicture(0), _lookingDirection('0'), _walkingDirection('0') {}

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
    //std::cout << "Before: " << _animationCounter << std::endl; 
    _animationCounter++;
    if(_animationCounter >= _picturesPerAnimation) {
        _animationCounter = 0;
    }
    //std::cout << "After: " <<_animationCounter << std::endl;
}

void Player::walkAndAnimate(const char direction) {
    if(direction == _walkingDirection) {
        nextAnimationCounter();
    } else {
        _animationCounter = 0;
    }

    switch (direction) {
        case '0':
            //nicht benötigt
            break;
        case 'W':
            _playerPicture = 1 + _animationCounter;
            _yCoordinate -= _walkingDistance;
            break;
        case 'A':
            _playerPicture = 1 + _picturesPerAnimation + _animationCounter;
            _xCoordinate -= _walkingDistance;
            break;
        case 'S':
            _playerPicture = 1 + (2 * _picturesPerAnimation) + _animationCounter;
            _yCoordinate += _walkingDistance;
            break;
        case 'D':
            _playerPicture = 1 + (3 * _picturesPerAnimation) + _animationCounter;
            _xCoordinate += _walkingDistance;
            break;
        default:
            break;
    }
    _walkingDirection = direction;
}