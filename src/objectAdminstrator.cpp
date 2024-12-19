#include "../include/ObjectAdminstrator.hpp"
#include <SDL2/SDL.h> 


ObjectAdministrator::ObjectAdministrator(int windowHeight, int windowWidth, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startZelle){
    _rowSize = windowWidth/anzRows;
    _columnSize = windowHeight/anzColumns;

    _anzRowsPerColumn = anzRows;

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

    startZelle = cellRow * anzColumns + cellCol;           //Startzelle des Spielers
}

void ObjectAdministrator::assignObjects(){
    std::vector<std::vector<int>> obstacles = readObjectsFromFile("Werte.txt");

    // obstacles[i][0] = X-Koordinate des Objekts i
    // obstacles[i][1] = Y-Koordiante des Objekts i
    // obstacles[i][2] = Breite des Objekts i
    // obstacles[i][3] = Höhe des Objekts i

    int zaehlerSeitLetzterZelle;

    int temp1 = obstacles.size();
    int temp2 = _dasGrid.size();

    for (int i = 0; i < temp1; i++) {
        zaehlerSeitLetzterZelle = 0;
        for (int j = 0; j < temp2; j++) {
            // Überprüfe, ob die Zelle mit dem Objekt überlappt
            if (checkOverlap(_dasGrid[j], obstacles[i][0], obstacles[i][1], obstacles[i][2], obstacles[i][3])) {
                _dasGrid[j].addObject(Object(obstacles[i]));
                zaehlerSeitLetzterZelle = 0;
            }
            else{
                zaehlerSeitLetzterZelle++;
            }

            if(zaehlerSeitLetzterZelle >= _anzRowsPerColumn){
                break;
            }
        }
    }
}

bool ObjectAdministrator::checkOverlap(const Zelle& dieZelle, int posX, int posY, int width, int height){
    bool overlapsX = dieZelle._xZellenPos < posX + width && dieZelle._xZellenPos + _rowSize > posX;
    bool overlapsY = dieZelle._yZellenPos < posY + height && dieZelle._yZellenPos + _columnSize > posY;
    return overlapsX && overlapsY;
}



int ObjectAdministrator::neueZelleErreicht(int idxVorher, int angrenzendeZelle){  //Figur erreicht das Ende der begangenen Zelle 
 switch (angrenzendeZelle) {
    case 0:     //rechts
        return idxVorher++;
    case 1:     //links
        return idxVorher--;
    case 2:     //oben
        return idxVorher-_rowSize;
    case 3:     //unten
        return idxVorher+_rowSize;
    default:
        return idxVorher;
 }
}

int ObjectAdministrator::checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight ,int idxZelle){
                                                                                //Spieler tritt völlig in neue Zelle ein, ändere Primärzelle
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


bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung,int idxZelle){  //<-- Entweder die Map oder der Spieler besitzt die Zelle in der der Spieler sich aufhält, wird lediglich übergeben hierfür und zum updaten

    std::vector<int> dieZellen = felderZuPruefen(idxZelle, richtung);

     int temp1 = _dasGrid.size();
     int temp2 = dieZellen.size();

    for(int i = 0; i < temp2; i++){
        if(dieZellen[i] < 0 || dieZellen[i] >= temp1) 
            continue;               //Wenn adressierte Zellen sich nicht im Grid aufhalten überspringe die Iteration zur nächsten, da negativ oder zu groß

        for (const Object& value : _dasGrid[dieZellen[i]]._surroundingObjects) {
            if(value.checkCollision(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung, yBewegung, richtung)){
                return true;                //Kollision erkannt
            }
        }
    }
    return false;                         //Keine Kollision erkannt
}

std::vector<int> ObjectAdministrator::felderZuPruefen(int idxVorher, int richtung){
    switch (richtung){
        case 0:     //rechts
            return {idxVorher, idxVorher + 1, idxVorher + 1 + _rowSize, idxVorher + 1 - _rowSize};
        case 1:     //links
            return {idxVorher, idxVorher -1 , idxVorher - 1 + _rowSize, idxVorher - 1 - _rowSize};
        case 2:     //oben
            return {idxVorher, idxVorher - _rowSize, idxVorher + 1 - _rowSize, idxVorher - 1 - _rowSize};
        case 3:     //unten
            return {idxVorher, idxVorher + _rowSize, idxVorher + 1 + _rowSize, idxVorher - 1 + _rowSize};
        default:
            return {0,0,0,0};    
    }
}

std::vector<std::vector<int>> ObjectAdministrator::readObjectsFromFile(const std::string& filename) {
    std::vector<std::vector<int>> result;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> numbers;
        std::stringstream ss(line);
        std::string number;

        // Zahlen getrennt durch Kommas extrahieren
        while (std::getline(ss, number, ',')) {
            try {
                numbers.push_back(std::stoi(number));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Fehler: Ungültige Zahl in der Zeile \"" << line << "\"" << std::endl;
                break;
            }
        }

        // Sicherstellen, dass genau 4 Zahlen vorhanden sind
        if (numbers.size() == 4) {
            result.push_back(numbers);
        } else {
            std::cerr << "Warnung: Zeile ignoriert, da sie keine 4 Zahlen enthält: \"" << line << "\"" << std::endl;
        }
    }

    file.close();
    return result;
}

ObjectAdministrator::ObjectAdministrator() {
    // Nichts zu sehen, nur ein Konstruktor der rein gar nichts macht
}


//Struct-Operationen

ObjectAdministrator::Zelle::Zelle(int xPos, int yPos):
     _xZellenPos(xPos), _yZellenPos(yPos) {}

void ObjectAdministrator::Zelle::addObject(const Object& neuesObjekt){
    _surroundingObjects.insert(neuesObjekt);
  }

ObjectAdministrator::Zelle::Zelle() {
    //Pure Leere
}

/* Sicherheitshalber wird provisorischer Code hier gesaved:

void ObjectAdministrator::assignObjects(){
//Hier Code um Objekte in die jeweiligen Raster reinzustecken, mit Textliste. Vorerst als Test, werde ich manuell ein paar Objekte reinschreiben zum Test, später wird das allgemein gemacht

std::vector<std::vector<int>> obstacles = readObjectsFromFile("Werte.txt");

                                                //obstacles[i][0] = X-Koordinate des Objekts i
                                                //obstacles[i][1] = Y-Koordiante des Objekts i
                                                //obstacles[i][2] = Breite des Objekts i
                                                //obstacles[i][3] = Höhe des Objekts i

 for(int i = 0; i < obstacles.size(); i++){
    for(int j = 0; j < _dasGrid.size(); j++){
        if(_dasGrid[j].xZellenPos <= obstacles[i][0] && _dasGrid[j].xZellenPos + rowSize >= obstacles[i][0] && _dasGrid[j].yZellenPos <= obstacles[i][1] && _dasGrid[j].yZellenPos + columnSize >= obstacles[i][1]){
            _dasGrid[j].addObject(Object(obstacles[i])); //Koordianten erkannt, Objekt befindet sich in Zelle

            if(_dasGrid[j].xZellenPos + rowSize >= obstacles[i][0] + obstacles[i][2] && _dasGrid[j].yZellenPos + columnSize >= obstacles[i][1] + obstacles[i][3]){
                break;
            }
        }

        if (_dasGrid[j].xZellenPos > obstacles[i][0] && _dasGrid[j].xZellenPos <= obstacles[i][0] + obstacles[i][2]){
            if(_dasGrid[j].yZellenPos <= obstacles[i][1] + obstacles[i][3] && _dasGrid[j].yZellenPos + columnSize >= obstacles[i][1] +  obstacles[i][3] ){
                _dasGrid[j].addObject(Object(obstacles[i])); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(_dasGrid[j].xZellenPos + rowSize >= obstacles[i][0] + obstacles[i][2]){
                    break;
                }
            }

            if(_dasGrid[j].yZellenPos <= obstacles[i][1] && _dasGrid[j].yZellenPos + columnSize >= obstacles[i][1]){
                _dasGrid[j].addObject(Object(obstacles[i])); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(_dasGrid[j].xZellenPos + rowSize >= obstacles[i][0] + obstacles[i][2]){
                    break;
                }
            }

        }


        if (_dasGrid[j].yZellenPos > obstacles[i][1] && _dasGrid[j].yZellenPos <= obstacles[i][1] + obstacles[i][3]){
            
            if(_dasGrid[j].xZellenPos <= obstacles[i][0] + obstacles[i][2] && _dasGrid[j].xZellenPos + rowSize >= obstacles[i][0] +  obstacles[i][2]){
                _dasGrid[j].addObject(Object(obstacles[i])); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(_dasGrid[j].yZellenPos + columnSize >= obstacles[i][1] + obstacles[i][3]){
                    break;
                }
            }
            
            if(_dasGrid[j].xZellenPos <= obstacles[i][0] && _dasGrid[j].xZellenPos + rowSize >= obstacles[i][0]){
                _dasGrid[j].addObject(Object(obstacles[i])); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(_dasGrid[j].yZellenPos + columnSize >= obstacles[i][1] + obstacles[i][3]){
                    break;
                }
            }

        }


    }
  }
}





*/