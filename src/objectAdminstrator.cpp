#include "../include/ObjectAdminstrator.hpp"
#include <SDL2/SDL.h> 

ObjectAdministrator::ObjectAdministrator(int window_height, int window_width, int anzColumns, int anzRows) {
    int rowSize = window_width / anzRows;
    int columnSize = window_height / anzColumns;

    _dasGrid = std::vector<Zelle>(anzRows * anzColumns);

    int tempX = -1;
    int tempY = -1;

    for(int i = 0; i < anzColumns; i++){
        for(int j = 0; j < anzRows; j++){
            _dasGrid[i*anzRows+j] = Zelle (tempX+1, tempY+1, tempX + rowSize, tempY + columnSize);
            tempX += rowSize;
        }
        tempX = -1;
        tempY += columnSize;
    }
    assignObjects();
}

void ObjectAdministrator::assignObjects(){
//Hier Code um Objekte in die jeweiligen Raster reinzustecken, mit Textliste. Vorerst als Test, werde ich manuell ein paar Objekte reinschreiben zum Test, später wird das allgemein gemacht

    std::vector<SDL_Rect> obstacles = {
        {300, 200, 100, 100}, // Hindernis 1
        {500, 300, 150, 50}   // Hindernis 2
    };
                                                //(x,y,_width,_height)

    for(int i = 0; i < obstacles.size(); i++){
        for(int j = 0; j < _dasGrid.size(); j++){
            if(_dasGrid[j]._xZellenPos <= obstacles[i].x && _dasGrid[j]._xZellenPos + _dasGrid[j]._width >= obstacles[i].x && _dasGrid[j]._yZellenPos <= obstacles[i].y && _dasGrid[j]._yZellenPos + _dasGrid[j]._height >= obstacles[i].y) {
                //Koordianten erkannt, Objekt befindet sich in Zelle
                _dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); 

                if(_dasGrid[j]._xZellenPos + _dasGrid[j]._width >= obstacles[i].x + obstacles[i].w && _dasGrid[j]._yZellenPos + _dasGrid[j]._height >= obstacles[i].y + obstacles[i].h) {
                    break;
                }
            }
            if(_dasGrid[j]._xZellenPos > obstacles[i].x && _dasGrid[j]._xZellenPos <= obstacles[i].x + obstacles[i].w) {
                if(_dasGrid[j]._yZellenPos <= obstacles[i].y + obstacles[i].h && _dasGrid[j]._yZellenPos + _dasGrid[j]._height >= obstacles[i].y +  obstacles[i].h ) {
                    //Koordianten erkannt, Objekt befindet sich in Zelle
                    _dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); 

                    if(_dasGrid[j]._xZellenPos + _dasGrid[j]._width >= obstacles[i].x + obstacles[i].w) {
                        break;
                    }
                }
                if(_dasGrid[j]._yZellenPos <= obstacles[i].y && _dasGrid[j]._yZellenPos + _dasGrid[j]._height >= obstacles[i].y) {
                    //Koordianten erkannt, Objekt befindet sich in Zelle
                    _dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); 

                    if(_dasGrid[j]._xZellenPos + _dasGrid[j]._width >= obstacles[i].x + obstacles[i].w) {
                        break;
                    }
                }
            }
            if(_dasGrid[j]._yZellenPos > obstacles[i].y && _dasGrid[j]._yZellenPos <= obstacles[i].y + obstacles[i].h) {
                if(_dasGrid[j]._xZellenPos <= obstacles[i].x + obstacles[i].w && _dasGrid[j]._xZellenPos + _dasGrid[j]._width >= obstacles[i].x +  obstacles[i].w ) {
                    //Koordianten erkannt, Objekt befindet sich in Zelle
                    _dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); 

                    if(_dasGrid[j]._yZellenPos + _dasGrid[j]._height >= obstacles[i].y + obstacles[i].h) {
                        break;
                    }
                }
                if(_dasGrid[j]._xZellenPos <= obstacles[i].x && _dasGrid[j]._xZellenPos + _dasGrid[j]._width >= obstacles[i].x) {
                    //Koordianten erkannt, Objekt befindet sich in Zelle
                    _dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); 

                    if(_dasGrid[j]._yZellenPos + _dasGrid[j]._height >= obstacles[i].y + obstacles[i].h) {
                        break;
                    }
                }
            }
        }
    }
}

//Figur erreicht das Ende der begangenen Zelle 
int ObjectAdministrator::neueZelleErreicht(int idxVorher, int angrenzendeZelle){
    switch (angrenzendeZelle) {
        case 0:     //rechts
            return idxVorher++;
        case 1:     //links
            return idxVorher--;
        case 2:     //oben
            return idxVorher - _anzRowsPerColumn;
        case 3:     //unten
            return idxVorher + _anzRowsPerColumn;
        default:
            break;
    }
}

//Spieler tritt völlig in neue Zelle ein, ändere Primärzelle
int ObjectAdministrator::checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int player_height ,int idxZelle){
    if(playerXPos + playerWidht < _dasGrid[idxZelle]._xZellenPos){
        return neueZelleErreicht(idxZelle, 1); 
    }
    else if(playerXPos > _dasGrid[idxZelle]._xZellenPos + _dasGrid[idxZelle]._width){
        return neueZelleErreicht(idxZelle, 0);
    }
    else if(playerYPos > _dasGrid[idxZelle]._yZellenPos + _dasGrid[idxZelle]._height){
        return neueZelleErreicht(idxZelle, 3);
    }
    else if(playerYPos + player_height < _dasGrid[idxZelle]._yZellenPos){
        return neueZelleErreicht(idxZelle, 2);
    }
}

//<-- Entweder die Map oder der Spieler besitzt die Zelle in der der Spieler sich aufhält, wird lediglich übergeben hierfür und zum updaten
bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int player_height, int xBewegung, int yBewegung, int richtung,int idxZelle) {  
    std::vector<int> dieZellen = felderZuPruefen(idxZelle, richtung);

    for(int i = 0; i < dieZellen.size(); i++){
        if(dieZellen[i] < 0 || dieZellen[i] >= _dasGrid.size()) {
            //Wenn adressierte Zellen sich nicht im Grid aufhalten überspringe die Iteration zur nächsten, da negativ oder zu groß
            continue;               
        }
        for (const Object& value : _dasGrid[dieZellen[i]]._surroundingObjects) {
            if(value.checkCollision(playerXPos, playerYPos, playerWidht, player_height, xBewegung, yBewegung, richtung)){
                //Kollision erkannt
                return true;                
            }
        }
        //Keine Kollision erkannt
        return false;                         
    }
}

std::vector<int> ObjectAdministrator::felderZuPruefen(int idxVorher, int richtung){
    switch (richtung){
        case 0:     //rechts
            return {idxVorher, idxVorher + 1, idxVorher + 1 + _anzRowsPerColumn, idxVorher + 1 - _anzRowsPerColumn};
        case 1:     //links
            return {idxVorher, idxVorher -1 , idxVorher - 1 + _anzRowsPerColumn, idxVorher - 1 - _anzRowsPerColumn};
        case 2:     //oben
            return {idxVorher, idxVorher - _anzRowsPerColumn, idxVorher + 1 - _anzRowsPerColumn, idxVorher - 1 - _anzRowsPerColumn};
        case 3:     //unten
            return {idxVorher, idxVorher + _anzRowsPerColumn, idxVorher + 1 + _anzRowsPerColumn, idxVorher - 1 + _anzRowsPerColumn};
        default:
            break;
    }
}

//Struct-Operationen

ObjectAdministrator::Zelle::Zelle(int xPos, int yPos, int width, int height):
    _zellenIdx(_idxCounter++), _xZellenPos(xPos), _yZellenPos(yPos), _height(height), _width(width) {}

void ObjectAdministrator::Zelle::addObject(const Object& neuesObjekt) {
    _surroundingObjects.insert(neuesObjekt);
}
