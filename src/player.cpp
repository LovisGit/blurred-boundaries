#include "include/Player.hpp"

Player::Player() :_xCoordinate(0), _yCoordinate(0) {}

int Player::getXCoordinate() const {
    return _xCoordinate;
}

int Player::getYCoordinate() const {
    return _yCoordinate;
}

void Player::setXCoordinate(int xCoordinate) {
    _xCoordinate = xCoordinate;
}

void Player::setYCoordinate(int yCoordinate) {
    _yCoordinate = yCoordinate;
}