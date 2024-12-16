#include "../include/Object.hpp"


Object::Object(int pXpos, int pYpos, int pHeight, int pWidth, std::vector<bool> pTestNecessary = {true,true,true,true}):
_xPos(pXpos), _yPos(pYpos), _height(pHeight), _width(pWidth), _testNecessary(pTestNecessary) {}

bool Object::checkCollision(int pPlayerXPos, int pPlayerYPos, int pXBewegung, int pYBewegung){
  if(pPlayerXPos+pXBewegung > _xPos || pPlayerXPos+pXBewegung < _xPos + _width || pPlayerYPos+pYBewegung > _yPos || pPlayerYPos+pYBewegung < _yPos + _height){
      return false;
  }
  return true;
}