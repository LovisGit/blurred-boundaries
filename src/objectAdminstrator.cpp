#include "../include/ObjectAdminstrator.hpp"

ObjectAdministrator::ObjectAdministrator(int windowHeight, int windowWidth, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startZelle) {
    _rowSize = windowWidth/anzRows;                             //Size of Row
    _columnSize = windowHeight/anzColumns;                      //Size of Column

    _anzRowsPerColumn = anzRows;                                // Used later on to determine the next cell the player walks to

    _dasGrid = std::vector<Zelle>(anzRows * anzColumns);

    int tempX = -1;
    int tempY = -1;

    for(int i = 0; i < anzColumns; i++){
        for(int j = 0; j < anzRows; j++){
            _dasGrid[i*anzRows+j] = Zelle (tempX+1, tempY+1);
            tempX += _rowSize;
        }
        tempX = -1;
        tempY += _columnSize;
    }
    assignObjects();

    int cellRow = static_cast<int>(playerYPos / _columnSize); // Column-Index
    int cellCol = static_cast<int>(playerXPos / _rowSize); // Row-Index

    startZelle = cellRow * anzRows + cellCol;           //Start-Cell of player, necessary to determine which cells to use to check the collision with the player and their objects
}

void ObjectAdministrator::assignObjects() {
    std::vector<std::vector<int>> obstacles = readObjectsFromFile(OBJECTS_1080p_PATH);

    // obstacles[i][0] = X-Coordinate of Object i
    // obstacles[i][1] = Y-Coordinate of Object i
    // obstacles[i][2] = Height of Object i
    // obstacles[i][3] = Width of Object i

    int zaehlerSeitLetzterZelle;

    int gridGroeße = _dasGrid.size();
    int obstacleFeldGroeße = obstacles.size();

    bool discoveredFirstCellWithObject = false;             //Important to reduce the amount of iteration since an object can at max be assigned to 2 * number of columns
    for (int i = 0; i < obstacleFeldGroeße; i++) {
        zaehlerSeitLetzterZelle = 0;
        for (int j = 0; j < gridGroeße; j++) {
            //Check an overlap of player and object
            if (checkOverlap(_dasGrid[j], obstacles[i][0], obstacles[i][1], obstacles[i][2], obstacles[i][3])) {
                _dasGrid[j].addObject(Object(obstacles[i]));
                discoveredFirstCellWithObject = true;
                zaehlerSeitLetzterZelle = 0;
            }
            else{
                zaehlerSeitLetzterZelle++;
            }

            if(zaehlerSeitLetzterZelle >= _anzRowsPerColumn && discoveredFirstCellWithObject) {
                break;
            }
        }
        discoveredFirstCellWithObject = false;
    }
}

bool ObjectAdministrator::checkOverlap(const Zelle& dieZelle, int posX, int posY, int width, int height) {
    // Check the overlap for the x-direction and y-direction separately
    bool overlapsX = dieZelle._xZellenPos < posX + width && dieZelle._xZellenPos + _rowSize > posX;
    bool overlapsY = dieZelle._yZellenPos < posY + height && dieZelle._yZellenPos + _columnSize > posY;

    return overlapsX && overlapsY;
}

//Player reaches end of cell he is standing and determines new one based on direction
int ObjectAdministrator::neueZelleErreicht(int idxVorher, int angrenzendeZelle) {   
    switch (angrenzendeZelle) {
        case 0: // right
            return ++idxVorher;
        case 1: // left
            return --idxVorher;
        case 2: // up
            return idxVorher - _anzRowsPerColumn;
        case 3: // down
            return idxVorher + _anzRowsPerColumn;
        default:
            return idxVorher;
    }
}

//Changes Cell player is standing on
int ObjectAdministrator::checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight ,int idxZelle) {
    if(playerXPos + playerWidht < _dasGrid[idxZelle]._xZellenPos){
        return neueZelleErreicht(idxZelle, 1); 
    }
    else if(playerXPos > _dasGrid[idxZelle]._xZellenPos + _rowSize){
        return neueZelleErreicht(idxZelle, 0);
    }
    else if(playerYPos > _dasGrid[idxZelle]._yZellenPos + _columnSize){
        return neueZelleErreicht(idxZelle, 3);
    }
    else if(playerYPos + playerHeight < _dasGrid[idxZelle]._yZellenPos){
        return neueZelleErreicht(idxZelle, 2);
    }
    return idxZelle;
}

//Primary function to call the moment the player moves around
bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung,int idxZelle) {
    std::vector<int> dieZellen = felderZuPruefen(idxZelle, richtung);

    int zellenGroeße = dieZellen.size();
    int gridGroeße = _dasGrid.size();

    for(int i = 0; i < zellenGroeße; i++){

        if(dieZellen[i] < 0 || dieZellen[i] >= gridGroeße) 
                continue;               //Skip iteration if adressed cell is not included in grid (basically when its idx is negative or to big for the grid to contain)
            
        for (const Object& value : _dasGrid[dieZellen[i]]._surroundingObjects) {
           if(value.checkCollision(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung, yBewegung, richtung)) {
            return true;            //Collision detected
           }
        }
    }    
    return false;                   //No Collision detected
}

//Ascertains the cells necessary to check for the collision near the player cell, the player cell included
std::vector<int> ObjectAdministrator::felderZuPruefen(int idxVorher, int richtung) {
    switch (richtung){
        case 0:     // right
            return {idxVorher, idxVorher + 1, idxVorher + 1 + _anzRowsPerColumn, idxVorher + 1 - _anzRowsPerColumn};
        case 1:     // left
            return {idxVorher, idxVorher -1 , idxVorher - 1 + _anzRowsPerColumn, idxVorher - 1 - _anzRowsPerColumn};
        case 2:     // up
            return {idxVorher, idxVorher - _anzRowsPerColumn, idxVorher + 1 - _anzRowsPerColumn, idxVorher - 1 - _anzRowsPerColumn};
        case 3:     // down
            return {idxVorher, idxVorher + _anzRowsPerColumn, idxVorher + 1 + _anzRowsPerColumn, idxVorher - 1 + _anzRowsPerColumn};
        default:
            return {0,0,0,0};    
    }
}

ObjectAdministrator::ObjectAdministrator() {
    ;
}

//Struct-Operations

ObjectAdministrator::Zelle::Zelle(int xPos, int yPos) : _xZellenPos(xPos), _yZellenPos(yPos) {}

void ObjectAdministrator::Zelle::addObject(const Object& neuesObjekt) {
    _surroundingObjects.insert(neuesObjekt);
}

ObjectAdministrator::Zelle::Zelle() {
    ;
}