#include <vector>
#include <set>
#include "Object.hpp"
#pragma once

class ObjectAdministrator {

private:

    //Indiziert alle Zellen mit aufsteigendem Idx
    static int _idxCounter;  

    int _windowHeight;
    int _windowWidht;
    int _anzRowsPerColumn;
    struct Zelle{
        int _zellenIdx;

        int _xZellenPos;
        int _yZellenPos;

        int _width;
        int _height; 

        std::set<Object> _surroundingObjects;

        Zelle(int xPos, int yPos, int width, int height);
        void addObject(const Object& neuesObjekt);
    };
    std::vector<Zelle> _dasGrid;
    
    void assignObjects();
    int neueZelleErreicht(int idxVorher, int richtung);
    std::vector<int> felderZuPruefen(int idxVorher, int richtung);

public:

    ObjectAdministrator(int windowHeight, int windowWidht, int anzColumns, int anzRows);

    int checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int idxZelle);
    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung, int idxZelle);

};