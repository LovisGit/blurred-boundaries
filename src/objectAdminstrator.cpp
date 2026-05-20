#include "../include/ObjectAdminstrator.hpp"

ObjectAdministrator::ObjectAdministrator() {}

ObjectAdministrator::ObjectAdministrator(int windowHeight, int windowWidth, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startCell) {
    _rowSize = windowWidth/anzRows;                             
    _columnSize = windowHeight/anzColumns;      

    // used later on to determine the next cell the player walks to
    _anzRowsPerColumn = anzRows;

    _theGrid = std::vector<Cell>(anzRows * anzColumns);

    int tempX = -1;
    int tempY = -1;

    for(int i = 0; i < anzColumns; i++) {
        for(int j = 0; j < anzRows; j++){
            _theGrid[i*anzRows+j] = Cell (tempX+1, tempY+1);
            tempX += _rowSize;
        }
        tempX = -1;
        tempY += _columnSize;
    }
    assignObjects();

    int cellRow = static_cast<int>(playerYPos / _columnSize); // Column-Index
    int cellCol = static_cast<int>(playerXPos / _rowSize); // Row-Index

    // start-Cell of player, necessary to determine which cells to use to check the collision with the player and their objects
    startCell = cellRow * anzRows + cellCol;
}

void ObjectAdministrator::assignObjects() {
    std::vector<std::vector<int>> obstacles = readObjectsFromFile(OBJECTS_PATH);

    // obstacles[i][0] = X-Coordinate of Object i
    // obstacles[i][1] = Y-Coordinate of Object i
    // obstacles[i][2] = Height of Object i
    // obstacles[i][3] = Width of Object i

    int counterSinceLastCell;

    int gridGroeße = _theGrid.size();
    int obstacleFeldGroeße = obstacles.size();

    bool discoveredFirstCellWithObject = false;             //Important to reduce the amount of iteration since an object can at max be assigned to 2 * number of columns
    for(int i = 0; i < obstacleFeldGroeße; i++) {
        counterSinceLastCell = 0;
        for(int j = 0; j < gridGroeße; j++) {
            //Check an overlap of player and object
            if(checkOverlap(_theGrid[j], obstacles[i][0], obstacles[i][1], obstacles[i][2], obstacles[i][3])) {
                _theGrid[j].addObject(Object(obstacles[i]));
                discoveredFirstCellWithObject = true;
                counterSinceLastCell = 0;
            } else {
                counterSinceLastCell++;
            }

            if(counterSinceLastCell >= _anzRowsPerColumn && discoveredFirstCellWithObject) {
                break;
            }
        }
        discoveredFirstCellWithObject = false;
    }
}

bool ObjectAdministrator::checkOverlap(const Cell& dieCell, int posX, int posY, int width, int height) {
    // Check the overlap for the x-direction and y-direction separately
    bool overlapsX = dieCell._xCellPos < posX + width && dieCell._xCellPos + _rowSize > posX;
    bool overlapsY = dieCell._yCellPos < posY + height && dieCell._yCellPos + _columnSize > posY;

    return overlapsX && overlapsY;
}

int ObjectAdministrator::newCellReached(int idxBefore, int angrenzendeCell) {   
    switch(angrenzendeCell) {
        case 0: // right
            return ++idxBefore;
        case 1: // left
            return --idxBefore;
        case 2: // up
            return idxBefore - _anzRowsPerColumn;
        case 3: // down
            return idxBefore + _anzRowsPerColumn;
        default:
            return idxBefore;
    }
}

int ObjectAdministrator::checkNewCell(int playerXPos, int playerYPos, int playerWidht, int playerHeight ,int idxCell) {
    if(playerXPos + playerWidht < _theGrid[idxCell]._xCellPos){
        return newCellReached(idxCell, 1); 
    }
    else if(playerXPos > _theGrid[idxCell]._xCellPos + _rowSize){
        return newCellReached(idxCell, 0);
    }
    else if(playerYPos > _theGrid[idxCell]._yCellPos + _columnSize){
        return newCellReached(idxCell, 3);
    }
    else if(playerYPos + playerHeight < _theGrid[idxCell]._yCellPos){
        return newCellReached(idxCell, 2);
    }
    return idxCell;
}

bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement, int yMovement, int direction,int idxCell) {
    std::vector<int> theCells = cellsToCheck(idxCell, direction);

    int CellnGroeße = theCells.size();
    int gridGroeße = _theGrid.size();

    for(int i = 0; i < CellnGroeße; i++){
        if(theCells[i] < 0 || theCells[i] >= gridGroeße) 
            // skip iteration if adressed cell is not included in grid (basically when its idx is negative or to big for the grid to contain)
            continue;
            
        for (const Object& value : _theGrid[theCells[i]]._surroundingObjects) {
            if(value.checkCollision(playerXPos, playerYPos, playerWidht, playerHeight, xMovement, yMovement, direction)) {
                //Collision detected
                return true;            
            }
        }
    }    
    // no Collision detected
    return false;
}

std::vector<int> ObjectAdministrator::cellsToCheck(int idxBefore, int direction) {
    switch(direction) {
        case 0:     // right
            return {idxBefore, idxBefore + 1, idxBefore + 1 + _anzRowsPerColumn, idxBefore + 1 - _anzRowsPerColumn};
        case 1:     // left
            return {idxBefore, idxBefore -1 , idxBefore - 1 + _anzRowsPerColumn, idxBefore - 1 - _anzRowsPerColumn};
        case 2:     // up
            return {idxBefore, idxBefore - _anzRowsPerColumn, idxBefore + 1 - _anzRowsPerColumn, idxBefore - 1 - _anzRowsPerColumn};
        case 3:     // down
            return {idxBefore, idxBefore + _anzRowsPerColumn, idxBefore + 1 + _anzRowsPerColumn, idxBefore - 1 + _anzRowsPerColumn};
        default:
            return {0,0,0,0};    
    }
}

//Struct-Operations

ObjectAdministrator::Cell::Cell() {}

ObjectAdministrator::Cell::Cell(int xPos, int yPos) : _xCellPos(xPos), _yCellPos(yPos) {}

void ObjectAdministrator::Cell::addObject(const Object& newObject) {
    _surroundingObjects.insert(newObject);
}