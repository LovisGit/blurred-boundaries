#include "../include/Object.hpp"
#include <iostream>

Object::Object(int pXpos, int pYpos, int pHeight, int pWidth):
          _xPos(pXpos), _yPos(pYpos), _height(pHeight), _width(pWidth) {}

bool Object::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung , int richtung) const {
    switch (richtung) {
        case 0:
            return checkCollisionRight(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);
        case 1:
            return checkCollisionLeft(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);

        case 2:
            return checkCollisionUp(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);

        case 3:
            return checkCollisionDown(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);
        default:      
            //wird eh nie angesprochen aber warum nicht
            std::cout << "Wait, that's illegal!\n";
            break;
    }
    //default
    return false;
}

bool Object::checkCollisionRight(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const {
    if(playerXPos+playerWidht+xBewegung > _xPos && playerYPos < _yPos+_height && playerYPos + playerHeight > _yPos) {
        //Player läuft rechts auf ein Objekt zu und kollidiert
        return true;       
    }
    //Illegale Bewegung wurde nicht erfasst
    return false;            
}

bool Object::checkCollisionLeft(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const {
    if(playerXPos + xBewegung < _xPos+_width && playerYPos < _yPos+_height && playerYPos + playerHeight > _yPos) {
        //Player läuft links auf ein Objekt zu und kollidiert
        return true;
    }
    //Illegale Bewegung wurde nicht erfasst
    return false;         
}

bool Object::checkCollisionUp(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const {
    if(playerYPos + yBewegung < _yPos + _height && playerXPos < _xPos + _width && playerXPos + playerWidht > _xPos) {
        //Player läuft nach oben auf das Objekt zu und kollidiert
        return true;
    }
    //Illegale Bewegung wurde nicht erfasst
    return false;
}

bool Object::checkCollisionDown(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const{
    if(playerYPos + yBewegung + playerHeight > _yPos && playerXPos < _xPos + _width && playerXPos + playerWidht > _xPos) {
        //Player läuft nach unten auf das Objekt zu und kollidiert
        return true;   
    }
    //Illegale Bewegung wurde nicht erfasst
    return false;          
}