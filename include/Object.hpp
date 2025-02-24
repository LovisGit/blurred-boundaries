#pragma once
#include <vector>

class Object{
private:
    // Position and Size of the Object
    int _xPos;
    int _yPos;
    int _height;
    int _width;

    //Checks the collision of the Object with the player depending on the direction it was walked on
    bool checkCollisionRight(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const;
    bool checkCollisionLeft(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung) const;
    bool checkCollisionUp(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const;
    bool checkCollisionDown(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yBewegung) const;

public:

    Object(std::vector<int> objektWerte);

    //Determines which of the checkCollision-Operations above is adressed for the suitable direction walked
    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung) const;

    //Important for assigning the objects to their cells
    bool operator<(const Object& other) const;
    int getX(){
        return _xPos;
    }
};

