#include <vector>
#pragma once

class Object{


//Attribute

  //Die Basis des Objekts wird ein Rechteck sein

  //Generische
int _xPos;
int _yPos;
int _height;
int _width;

  //Falls eine Seite des Objekts eh niemals vom Spieler berührt werden kann, gibt es keinen Grund die abzufragen wenn auf false
std::vector<bool> _testNecessary;

Object(int pXpos, int pYpos, int pHeight, int pWidth, std::vector<bool> pTestNecessary = {true,true,true,true});
bool checkCollision(int pPlayerXPos, int pPlayerYPos, int pXBewegung, int pYBewegung);

};