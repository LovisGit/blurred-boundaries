#include "../include/Object.hpp"
#include <iostream>

Object::Object(std::vector<int> objektWerte):
_xPos(objektWerte[0]), _yPos(objektWerte[1]), _height(objektWerte[3]), _width(objektWerte[2]) {}

bool Object::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung , int richtung) const{

  switch (richtung) {
    case 0:
      return checkCollisionRight(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);

    case 1:
      return checkCollisionLeft(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);

    case 2:
      return checkCollisionUp(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);

    case 3:
      return checkCollisionDown(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung);

  default:      //wird eh nie angesprochen aber warum nicht
    std::cout << "Wait, that's illegal!\n";
    break;
  }
}



bool Object::checkCollisionRight(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const {
  if(playerXPos+playerWidht+xBewegung > _xPos && playerYPos < _yPos+_height && playerYPos + playerHeight > _yPos){
    return true;         //Player läuft rechts auf ein Objekt zu und kollidiert
  }
  return false;            //Illegale Bewegung wurde nicht erfasst
}

bool Object::checkCollisionLeft(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const {
  if(playerXPos + xBewegung < _xPos+_width && playerYPos < _yPos+_height && playerYPos + playerHeight > _yPos){
    return true;         //Player läuft links auf ein Objekt zu und kollidiert
  }
  return false;            //Illegale Bewegung wurde nicht erfasst
}

bool Object::checkCollisionUp(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const {
  if(playerYPos + yBewegung < _yPos + _height && playerXPos < _xPos + _width && playerXPos + playerWidht > _xPos){
    return true;         //Player löuft nach oben auf das Objekt zu und kollidiert
  }
  return false;            //Illegale Bewegung wurde nicht erfasst
}

bool Object::checkCollisionDown(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const{
  if(playerYPos + yBewegung + playerHeight > _yPos && playerXPos < _xPos + _width && playerXPos + playerWidht > _xPos){
    return true;         //Player läuft nach unten auf das Objekt zu und kollidiert
  }
  return false;            //Illegale Bewegung wurde nicht erfasst
}