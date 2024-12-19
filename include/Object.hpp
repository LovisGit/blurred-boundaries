#pragma once
#include <vector>

class Object{

private:

    //Generische Attribute
    int _xPos;
    int _yPos;
    int _height;
    int _width;

    //Selbsterklärend
    bool checkCollisionRight(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const;
    bool checkCollisionLeft(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const;
    bool checkCollisionUp(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const;
    bool checkCollisionDown(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const;

public:

Object(std::vector<int> objektWerte);
//Konstruktur für die Objekte

    //Determiniert welche Kollisionsfunktion angesprochen wird im Falle einer Bewegung
    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung) const;
    bool operator<(const Object& other) const;
};