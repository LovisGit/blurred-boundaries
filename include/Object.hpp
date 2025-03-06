#pragma once
#include "Constants.hpp"

class Object{
private:
    int _xPos;
    int _yPos;
    int _height;
    int _width;

    // checks the collision of the Object with the player depending on the direction it was walked on
    bool checkCollisionRight(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement) const;
    bool checkCollisionLeft(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement) const;
    bool checkCollisionUp(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yMovement) const;
    bool checkCollisionDown(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int yMovement) const;

public:
    Object(std::vector<int> objectValues);

    // determines which of the checkCollision-Operations above is adressed for the suitable direction walked
    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement, int yMovement, int direction) const;

    // important for assigning the objects to their cells
    bool operator<(const Object& other) const;
};

