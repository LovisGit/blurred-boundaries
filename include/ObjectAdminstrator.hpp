#include <vector>
#include <set>
#include "Object.hpp"
#pragma once

class ObjectAdministrator{

private:

 static int idxCounter;      //Indiziert aklle Zellen mit aufsteigendem Idx


 int windowHeight;
 int windowWidht;

 int anzRowsPerColumn;


 struct Zelle{
  int zellenIdx;

  int xZellenPos;
  int yZellenPos;

  int width;
  int height; 

  std::set<Object> surroundingObjects;


  Zelle(int pXPos, int pYPos, int pWidth, int pHeight);
  void addObject(const Object& neuesObjekt);
};


 std::vector<Zelle> dasGrid;
 
 void assignObjects();

 int neueZelleErreicht(int pIdxVorher, int pRichtung);

 std::vector<int> felderZuPruefen(int pIdxVorher, int richtung);
 
public:

 ObjectAdministrator(int pWindowHeight, int pWindowWidht, int pAnzColumns, int pAnzRows);

 int checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int pIdxZelle);

 bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung, int pIdxZelle);

};