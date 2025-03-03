#include "../include/Object.hpp"
#include <iostream>

Object::Object(std::vector<int> objectValues) : _xPos(objectValues[0]), _yPos(objectValues[1]), _height(objectValues[3]), _width(objectValues[2]) {}

bool Object::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung , int richtung) const {
    switch (richtung) {
        case 0:
            return checkCollisionRight(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);
        case 1:
            return checkCollisionLeft(playerXPos, playerYPos, playerWidht, playerHeight, (-1)*xBewegung);
        case 2:
            return checkCollisionUp(playerXPos, playerYPos, playerWidht, playerHeight, (-1)*yBewegung);
        case 3:
            return checkCollisionDown(playerXPos, playerYPos, playerWidht, playerHeight, yBewegung);
        default:
            break;
    }
    //default
    return false;
}

bool Object::checkCollisionRight(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement) const {
    if(playerXPos+playerWidht+xMovement > _xPos && playerYPos < _yPos+_height && playerYPos + playerHeight > _yPos && _xPos > playerXPos) {
        // player walks right and collides with this object
        return true;       
    }
    // illegal movement (Collision) identified
    return false;            
}

bool Object::checkCollisionLeft(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement) const {
    if(playerXPos + xMovement < _xPos+_width && playerYPos < _yPos+_height && playerYPos + playerHeight > _yPos && _xPos < playerXPos) {
        // player walks left and collides with this object
        return true;
    }
    // illegal movement (Collision) identified
    return false;         
}

bool Object::checkCollisionUp(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yMovement) const {
    if(playerYPos + yMovement < _yPos + _height && playerXPos < _xPos + _width && playerXPos + playerWidht > _xPos && _yPos < playerYPos) {
        // player walks up and collides with this object
        return true;
    }
    // illegal movement (Collision) identified
    return false;
}

bool Object::checkCollisionDown(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yMovement) const{
    if(playerYPos + yMovement + playerHeight > _yPos && playerXPos < _xPos + _width && playerXPos + playerWidht > _xPos && _yPos > playerYPos) {
        // player walks down and collides with this object
        return true;   
    }
    // illegal movement (Collision) identified
    return false;          
}

bool Object::operator<(const Object& other) const {
    if (this->_xPos != other._xPos) {
        return this->_xPos < other._xPos;
    }
    if (this->_yPos != other._yPos) {
        return this->_yPos < other._yPos;
    }
    if (this->_width != other._width) {
        return this->_width < other._width;
    }
    return this->_height < other._height;
}
