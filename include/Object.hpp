#pragma once

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

    //Konstruktur für die Objekte
    Object(int pXpos, int pYpos, int pHeight, int pWidth);

    //Determiniert welche Kollisionsfunktion angesprochen wird im Falle einer Bewegung
    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung) const;

};