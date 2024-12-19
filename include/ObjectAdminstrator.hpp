#include <vector>
#include <set>
#include "Object.hpp"
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ObjectAdministrator{

private:
    
 int _rowSize;
 int _columnSize;

 int _anzRowsPerColumn;


 struct Zelle{

  int _xZellenPos;
  int _yZellenPos;

  std::set<Object> _surroundingObjects;

  Zelle();  //Der Scheiß-Standardkonstruktor wird normalerweise vom Kompiler erzeugt aber naja gut, ansonsten wird rumgemeckert...
  
  Zelle(int xPos, int yPos);
  void addObject(const Object& neuesObjekt);
};


 std::vector<Zelle> _dasGrid;
 
 void assignObjects();                                                //fügt den erzeugten Zellen ihre Objekte je nach angegebenen Koordinaten an

 int neueZelleErreicht(int idxVorher, int richtung);                //hilft die Zellen außenrum zu lokalisieren

 std::vector<int> felderZuPruefen(int idxVorher, int richtung);      //Gedacht für die CheckCollision, wählt die zugeprüften Zelle aus je nach Richtung

 bool checkOverlap(const Zelle& zelle, int posX, int posY, int width, int height);    //Für assignObject, hilft für einen besseren Überblick des Codes

public:

 ObjectAdministrator(int windowHeight, int windowWidht, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startZelle);  //aufgerufen von externer Klasse

 ObjectAdministrator();

 int checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int pIdxZelle);  //schaut ob der Spieler vollkommen in eine neue Zelle eindringt, wenn ja wird geupdatet

 bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung, int idxZelle);  //selbsterklärend

 static std::vector<std::vector<int>> readObjectsFromFile(const std::string& filename);
};