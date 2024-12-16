#include <vector>
#include <set>
#include "object.hpp"

class ObjectAdministrator{

static int idxCounter;      //Indiziert Zellen mit Idx

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
};


std::vector<Zelle> dasGrid;
 

ObjectAdministrator(int pWindowHeight, int pWindowWidht, int pAnzColumns, int pAnzRows);
void assignObjects();

int neueZelleErreicht(int pIdxVorher, int pRichtung);

bool checkCollision(int pIdxZelle);

};