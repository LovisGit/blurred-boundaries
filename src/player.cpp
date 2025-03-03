#include "../include/Player.hpp"

Player::Player(const int xCoordinate, const int yCoordinate, const int playerWidth, const int playerHeight, 
               const int picturesPerAnimation, const int walkingDistance) 
                : 
                _xCoordinate(xCoordinate), _yCoordinate(yCoordinate), _playerWidth(playerWidth), _playerHeight(playerHeight),
                _picturesPerAnimation(picturesPerAnimation), _walkingDistance(walkingDistance), 
                _animationCounter(0), _playerPicture(0), _walkingDirection(0), _keysDown({0}) {
    theObjectManager = ObjectAdministrator(WINDOW_HEIGHT, WINDOW_WIDTH, NUMBER_OF_COLUMNS, NUMBER_OF_ROWS, PLAYER_START_X, PLAYER_START_Y, _currentCell);
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

    // changes the coordinates and the playerimage
    if(_keysDown[0]) {
        _playerPicture = (2 * _picturesPerAnimation) + _animationCounter;
        if(checkCollisionPlayer(2)){
        _yCoordinate -= _walkingDistance;
        }
    }
    if(_keysDown[1]) {
        _playerPicture = (3 * _picturesPerAnimation) + _animationCounter;
        if(checkCollisionPlayer(1)){
        _xCoordinate -= _walkingDistance;
        }
    }
    if(_keysDown[2]) {
        _playerPicture = (0 * _picturesPerAnimation) + _animationCounter;
        if(checkCollisionPlayer(3)){
        _yCoordinate += _walkingDistance;
        }
    }
    if(_keysDown[3]) {
        _playerPicture = (1 * _picturesPerAnimation) + _animationCounter;
        if(checkCollisionPlayer(0)){
        _xCoordinate += _walkingDistance;
        }
    }

    _currentCell = theObjectManager.checkNewCell(_xCoordinate, _yCoordinate, PLAYER_WIDTH, PLAYER_HEIGHT, _currentCell);
    _walkingDirection = direction;
}

bool Player::checkCollisionPlayer(int direction){
    return !theObjectManager.checkCollision(_xCoordinate, _yCoordinate, PLAYER_WIDTH, PLAYER_HEIGHT, WALKING_DISTANCE, WALKING_DISTANCE, direction, _currentCell);
}