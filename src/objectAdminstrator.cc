#include "../include/ObjectAdminstrator.hpp"


ObjectAdministrator::Zelle::Zelle(int pXPos, int pYPos, int pWidth, int pHeight):
    zellenIdx(idxCounter++), xZellenPos(pXPos), yZellenPos(pYPos), height(pHeight), width(pWidth)
{


}

ObjectAdministrator::ObjectAdministrator(int pWindowHeight, int pWindowWidth, int pAnzColumns, int pAnzRows){
    int rowSize = pWindowWidth/pAnzRows;
    int columnSize = pWindowHeight/pAnzColumns;

    dasGrid[rowSize*columnSize];

    int tempX = -1;
    int tempY = -1;

    for(int i = 0; i < pAnzColumns; i++){
        for(int j = 0; j < pAnzRows; i++){
            Zelle dasGrid[i*pAnzRows+j](tempX+1, tempY+1, tempX + rowSize, tempY + columnSize);
            tempX = tempX + rowSize;
            tempY = tempY + columnSize;
        }
        tempX = -1;
        tempY = -1;
    }

    assignObjects();
}

void ObjectAdministrator::assignObjects(){
//Hier Code um Objekte in die jeweiligen Raster reinzustecken, mit Textliste. Vorerst als Test, werde ich manuell ein paar Objekte reinschreiben zum Test, später wird das allgemein gemacht
}

int ObjectAdministrator::neueZelleErreicht(int pIdxVorher, int pRichtung){  //Figur erreicht das Ende der begangenen Zelle 
switch (pRichtung)
{
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

bool ObjectAdministrator::checkCollision(int pIdxZelle){

}