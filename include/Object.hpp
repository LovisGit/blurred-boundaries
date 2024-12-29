#pragma once
#include <vector>

class Object{


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

int getX() const { return _xPos; }
int getY() const { return _yPos; }
int getH() const { return _height; }
int getW() const { return _width; }

Object(std::vector<int> objektWerte);
//Konstruktur für die Objekte
    //Determiniert welche Kollisionsfunktion angesprochen wird im Falle einer Bewegung
    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung) const;
    bool operator<(const Object& other) const;
    int getX(){
        return _xPos;
    }
};

