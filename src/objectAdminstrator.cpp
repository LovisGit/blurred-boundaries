#include "../include/ObjectAdminstrator.hpp"

ObjectAdministrator::ObjectAdministrator(int windowHeight, int windowWidth, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startZelle) {
    _rowSize = windowWidth/anzRows;                             //Größe einer Spalte
    _columnSize = windowHeight/anzColumns;                      //Größe einer Zeile

    _anzRowsPerColumn = anzRows;                                //Die Anzahl der Spalten wird hier gespeichert, damit man sie verwenden kann um die Spielerposition zu berechnen

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

    int cellRow = static_cast<int>(playerYPos / _columnSize); // Zeilenindex
    int cellCol = static_cast<int>(playerXPos / _rowSize); // Spaltenindex

    startZelle = cellRow * anzRows + cellCol;           //Startzelle des Spielers
}

void ObjectAdministrator::assignObjects() {
    std::vector<std::vector<int>> obstacles = readObjectsFromFile(OBJECTS_1080p_PATH);

    // obstacles[i][0] = X-Koordinate des Objekts i
    // obstacles[i][1] = Y-Koordiante des Objekts i
    // obstacles[i][2] = Breite des Objekts i
    // obstacles[i][3] = Höhe des Objekts i

    int zaehlerSeitLetzterZelle;

    int gridGroeße = _dasGrid.size();
    int obstacleFeldGroeße = obstacles.size();

    bool discoveredFirstCellWithObject = false;             //Wichtig dass das 
    for (int i = 0; i < obstacleFeldGroeße; i++) {
        zaehlerSeitLetzterZelle = 0;
        for (int j = 0; j < gridGroeße; j++) {
            // Überprüfe, ob die Zelle mit dem Objekt überlappt
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
    // Prüfe Überlappung in X- und Y-Richtung
    bool overlapsX = dieZelle._xZellenPos < posX + width && dieZelle._xZellenPos + _rowSize > posX;
    bool overlapsY = dieZelle._yZellenPos < posY + height && dieZelle._yZellenPos + _columnSize > posY;

    return overlapsX && overlapsY;
}

// Figur erreicht das Ende der begangenen Zelle
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

//Spieler tritt völlig in neue Zelle ein, ändere Primärzelle
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

// Entweder die Map oder der Spieler besitzt die Zelle in der der Spieler sich aufhält, wird lediglich übergeben hierfür und zum updaten
bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung,int idxZelle) {
    std::vector<int> dieZellen = felderZuPruefen(idxZelle, richtung);

    int zellenGroeße = dieZellen.size();
    int gridGroeße = _dasGrid.size();

    for(int i = 0; i < zellenGroeße; i++){

        if(dieZellen[i] < 0 || dieZellen[i] >= gridGroeße) 
            continue;               //Wenn adressierte Zellen sich nicht im Grid aufhalten überspringe die Iteration zur nächsten, da negativ oder zu groß
            
        for (const Object& value : _dasGrid[dieZellen[i]]._surroundingObjects) {
           if(value.checkCollision(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung, yBewegung, richtung)) {
            return true;
           }
        }
    }    
    return false;                   //Keine Kollision erkannt
}

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
    // Nichts zu sehen, nur ein Konstruktor der rein gar nichts macht
}

//Struct-Operationen

ObjectAdministrator::Zelle::Zelle(int xPos, int yPos) : _xZellenPos(xPos), _yZellenPos(yPos) {}

void ObjectAdministrator::Zelle::addObject(const Object& neuesObjekt) {
    _surroundingObjects.insert(neuesObjekt);
}

ObjectAdministrator::Zelle::Zelle() {
    //Pure Leere
}