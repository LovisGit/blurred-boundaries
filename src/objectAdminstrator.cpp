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

    for(int i = 0; i < anzColumns; i++){
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

    int zaehlerSeitLetzterCell;

    int gridGroeße = _theGrid.size();
    int obstacleFeldGroeße = obstacles.size();

    bool discoveredFirstCellWithObject = false;             //Important to reduce the amount of iteration since an object can at max be assigned to 2 * number of columns
    for (int i = 0; i < obstacleFeldGroeße; i++) {
        zaehlerSeitLetzterCell = 0;
        for (int j = 0; j < gridGroeße; j++) {
            //Check an overlap of player and object
            if (checkOverlap(_theGrid[j], obstacles[i][0], obstacles[i][1], obstacles[i][2], obstacles[i][3])) {
                _theGrid[j].addObject(Object(obstacles[i]));
                discoveredFirstCellWithObject = true;
                zaehlerSeitLetzterCell = 0;
            }
            else{
                zaehlerSeitLetzterCell++;
            }

            if(zaehlerSeitLetzterCell >= _anzRowsPerColumn && discoveredFirstCellWithObject) {
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

// player reaches end of cell he is standing and determines new one based on direction
int ObjectAdministrator::newCellReached(int idxBefore, int angrenzendeCell) {   
    switch (angrenzendeCell) {
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

// changes Cell player is standing on
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

// primary function to call the moment the player moves around
bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement, int yMovement, int richtung,int idxCell) {
    std::vector<int> dieCelln = cellsToCheck(idxCell, richtung);

    int CellnGroeße = dieCelln.size();
    int gridGroeße = _theGrid.size();

    for(int i = 0; i < CellnGroeße; i++){
        if(dieCelln[i] < 0 || dieCelln[i] >= gridGroeße) 
            // skip iteration if adressed cell is not included in grid (basically when its idx is negative or to big for the grid to contain)
            continue;
            
        for (const Object& value : _theGrid[dieCelln[i]]._surroundingObjects) {
            if(value.checkCollision(playerXPos, playerYPos, playerWidht, playerHeight, xMovement, yMovement, richtung)) {
                //Collision detected
                return true;            
            }
        }
    }    
    // no Collision detected
    return false;
}

// ascertains the cells necessary to check for the collision near the player cell, the player cell included
std::vector<int> ObjectAdministrator::cellsToCheck(int idxBefore, int direction) {
    switch (direction){
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

ObjectAdministrator::Cell::Cell(int xPos, int yPos) : _xCellPos(xPos), _yCellPos(yPos) {}

void ObjectAdministrator::Cell::addObject(const Object& newObject) {
    _surroundingObjects.insert(newObject);
}

ObjectAdministrator::Cell::Cell() {}