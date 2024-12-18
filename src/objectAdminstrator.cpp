#include "../include/ObjectAdminstrator.hpp"
#include <SDL2/SDL.h> 


ObjectAdministrator::ObjectAdministrator(int pWindowHeight, int pWindowWidth, int pAnzColumns, int pAnzRows){
    int rowSize = pWindowWidth/pAnzRows;
    int columnSize = pWindowHeight/pAnzColumns;

    dasGrid = std::vector<Zelle>(pAnzRows * pAnzColumns);

    int tempX = -1;
    int tempY = -1;

    for(int i = 0; i < pAnzColumns; i++){
        for(int j = 0; j < pAnzRows; j++){
            dasGrid[i*pAnzRows+j] = Zelle (tempX+1, tempY+1, tempX + rowSize, tempY + columnSize);
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



                                                //(x,y,width,height)

 for(int i = 0; i < obstacles.size(); i++){
    for(int j = 0; j < dasGrid.size(); j++){
        if(dasGrid[j].xZellenPos <= obstacles[i].x && dasGrid[j].xZellenPos + dasGrid[j].width >= obstacles[i].x && dasGrid[j].yZellenPos <= obstacles[i].y && dasGrid[j].yZellenPos + dasGrid[j].height >= obstacles[i].y){
            dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); //Koordianten erkannt, Objekt befindet sich in Zelle

            if(dasGrid[j].xZellenPos + dasGrid[j].width >= obstacles[i].x + obstacles[i].w && dasGrid[j].yZellenPos + dasGrid[j].height >= obstacles[i].y + obstacles[i].h){
                break;
            }
        }

        if (dasGrid[j].xZellenPos > obstacles[i].x && dasGrid[j].xZellenPos <= obstacles[i].x + obstacles[i].w){
            if(dasGrid[j].yZellenPos <= obstacles[i].y + obstacles[i].h && dasGrid[j].yZellenPos + dasGrid[j].height >= obstacles[i].y +  obstacles[i].h ){
                dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(dasGrid[j].xZellenPos + dasGrid[j].width >= obstacles[i].x + obstacles[i].w){
                    break;
                }
            }

            if(dasGrid[j].yZellenPos <= obstacles[i].y && dasGrid[j].yZellenPos + dasGrid[j].height >= obstacles[i].y){
                dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(dasGrid[j].xZellenPos + dasGrid[j].width >= obstacles[i].x + obstacles[i].w){
                    break;
                }
            }

        }


        if (dasGrid[j].yZellenPos > obstacles[i].y && dasGrid[j].yZellenPos <= obstacles[i].y + obstacles[i].h){
            
            if(dasGrid[j].xZellenPos <= obstacles[i].x + obstacles[i].w && dasGrid[j].xZellenPos + dasGrid[j].width >= obstacles[i].x +  obstacles[i].w ){
                dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(dasGrid[j].yZellenPos + dasGrid[j].height >= obstacles[i].y + obstacles[i].h){
                    break;
                }
            }
            
            if(dasGrid[j].xZellenPos <= obstacles[i].x && dasGrid[j].xZellenPos + dasGrid[j].width >= obstacles[i].x){
                dasGrid[i].addObject(Object(obstacles[i].x , obstacles[i].y, obstacles[i].h, obstacles[i].w)); //Koordianten erkannt, Objekt befindet sich in Zelle

                if(dasGrid[j].yZellenPos + dasGrid[j].height >= obstacles[i].y + obstacles[i].h){
                    break;
                }
            }

        }


    }
  }
}

int ObjectAdministrator::neueZelleErreicht(int pIdxVorher, int angrenzendeZelle){  //Figur erreicht das Ende der begangenen Zelle 
 switch (angrenzendeZelle) {
    case 0:     //rechts
        return pIdxVorher++;
    case 1:     //links
        return pIdxVorher--;
    case 2:     //oben
        return pIdxVorher-anzRowsPerColumn;
    case 3:     //unten
        return pIdxVorher+anzRowsPerColumn;
    default:
        break;
 }
}

int ObjectAdministrator::checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight ,int pIdxZelle){
                                                                                //Spieler tritt völlig in neue Zelle ein, ändere Primärzelle
    if(playerXPos + playerWidht < dasGrid[pIdxZelle].xZellenPos){
        return neueZelleErreicht(pIdxZelle, 1); 
    }
    else if(playerXPos > dasGrid[pIdxZelle].xZellenPos + dasGrid[pIdxZelle].width){
        return neueZelleErreicht(pIdxZelle, 0);
    }
    else if(playerYPos > dasGrid[pIdxZelle].yZellenPos + dasGrid[pIdxZelle].height){
        return neueZelleErreicht(pIdxZelle, 3);
    }
    else if(playerYPos + playerHeight < dasGrid[pIdxZelle].yZellenPos){
        return neueZelleErreicht(pIdxZelle, 2);
    }
}


bool ObjectAdministrator::checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung,int pIdxZelle){  //<-- Entweder die Map oder der Spieler besitzt die Zelle in der der Spieler sich aufhält, wird lediglich übergeben hierfür und zum updaten

    std::vector<int> dieZellen = felderZuPruefen(pIdxZelle, richtung);

    for(int i = 0; i < dieZellen.size(); i++){
        if(dieZellen[i] < 0 || dieZellen[i] >= dasGrid.size()) 
            continue;               //Wenn adressierte Zellen sich nicht im Grid aufhalten überspringe die Iteration zur nächsten, da negativ oder zu groß

        for (const Object& value : dasGrid[dieZellen[i]].surroundingObjects) {
            if(value.checkCollision(playerXPos, playerYPos, playerWidht, playerHeight, xBewegung, yBewegung, richtung)){
                return true;                //Kollision erkannt
            }
        }
    return false;                         //Keine Kollision erkannt
    }
}

std::vector<int> ObjectAdministrator::felderZuPruefen(int pIdxVorher, int richtung){
    switch (richtung){
        case 0:     //rechts
            return {pIdxVorher, pIdxVorher + 1, pIdxVorher + 1 + anzRowsPerColumn, pIdxVorher + 1 - anzRowsPerColumn};
        case 1:     //links
            return {pIdxVorher, pIdxVorher -1 , pIdxVorher - 1 + anzRowsPerColumn, pIdxVorher - 1 - anzRowsPerColumn};
        case 2:     //oben
            return {pIdxVorher, pIdxVorher - anzRowsPerColumn, pIdxVorher + 1 - anzRowsPerColumn, pIdxVorher - 1 - anzRowsPerColumn};
        case 3:     //unten
            return {pIdxVorher, pIdxVorher + anzRowsPerColumn, pIdxVorher + 1 + anzRowsPerColumn, pIdxVorher - 1 + anzRowsPerColumn};
        default:
            break;
    }
}

//Struct-Operationen

ObjectAdministrator::Zelle::Zelle(int pXPos, int pYPos, int pWidth, int pHeight):
    zellenIdx(idxCounter++), xZellenPos(pXPos), yZellenPos(pYPos), height(pHeight), width(pWidth) {}

void ObjectAdministrator::Zelle::addObject(const Object& neuesObjekt){
    surroundingObjects.insert(neuesObjekt);
  }
