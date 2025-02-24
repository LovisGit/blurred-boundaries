#pragma once
#include "Object.hpp"
#include "Constants.hpp"

class ObjectAdministrator{                          
private:
    int _rowSize;              
    int _columnSize;

    int _anzRowsPerColumn;

    // Map is structered as a Grid with each Cell possessing multiple Objects
    struct Zelle{
        int _xZellenPos;
        int _yZellenPos;

        std::set<Object> _surroundingObjects;

        Zelle();  //Standard-Constructor
        
        Zelle(int xPos, int yPos);
        void addObject(const Object& neuesObjekt);      //inserted in _surroundingObjects a new Object                  
    };

    std::vector<Zelle> _dasGrid;
    
    //inserts into the created cell objects corresponding to both of their coordinates and sizes 
    void assignObjects();

    //returns the idx of a new cell the moment the player leaves his current cell
    int neueZelleErreicht(int idxVorher, int richtung);                 

    //Necessary to determine which cells to check for collision depending on the the cell the player is currently standing in and his walking direction
    std::vector<int> felderZuPruefen(int idxVorher, int richtung);      

    //Hear, the overlap is directly checked
    bool checkOverlap(const Zelle& zelle, int posX, int posY, int width, int height);

public:
    ObjectAdministrator();

    //called through the player class
    ObjectAdministrator(int windowHeight, int windowWidht, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startZelle);  

    //the moment the player leaves their current cell completely, returns idx of the new player cell
    int checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int pIdxZelle);  

    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung, int idxZelle);
};

//Function reads out values in that form for each row: x,y,width,height (if a row does not posses that structure, it gets skipped) ; used in assignObject()
inline std::vector<std::vector<int>> readObjectsFromFile(const std::string& filename) {
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

        if (line.empty() || line[0] == '#' || line[0] == '/') {
            continue;
        }
        // Extract numbers separated by a comma
        while (std::getline(ss, number, ',')) {
            try {
                numbers.push_back(std::stoi(number));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Fehler: Ungültige Zahl in der Zeile \"" << line << "\"" << std::endl;
                break;
            }
        }

        // Check if actually four numbers were recognized
        if (numbers.size() == 4) {
            result.push_back(numbers);
        } else {
            std::cerr << "Warnung: Zeile ignoriert, da sie keine 4 Zahlen enthält: \"" << line << "\"" << std::endl;
        }
    }

    file.close();
    return result;
}
