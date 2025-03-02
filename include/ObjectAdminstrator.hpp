#pragma once
#include "Constants.hpp"
#include "Object.hpp"

class ObjectAdministrator{                          
private:
    int _rowSize;              
    int _columnSize;
    int _anzRowsPerColumn;

    // map is structered as a Grid with each Cell possessing multiple Objects
    struct Cell {
        int _xCellPos;
        int _yCellPos;

        std::set<Object> _surroundingObjects;

        Cell();  // standard-Constructor
        
        Cell(int xPos, int yPos);

        // inserted in _surroundingObjects a new Object 
        void addObject(const Object& newObbject);
    };

    std::vector<Cell> _theGrid;
    
    // inserts into the created cell objects corresponding to both of their coordinates and sizes 
    void assignObjects();

    // returns the idx of a new cell the moment the player leaves his current cell
    int newCellReached(int idxBefore, int direction);                 

    // necessary to determine which cells to check for collision depending on the the cell the player is currently standing in and his walking direction
    std::vector<int> cellsToCheck(int idxBefore, int direction);      

    // hear, the overlap is directly checked
    bool checkOverlap(const Cell& Cell, int posX, int posY, int width, int height);

public:
    ObjectAdministrator();

    // called through the player class
    ObjectAdministrator(int windowHeight, int windowWidht, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startCell);  

    // the moment the player leaves their current cell completely, returns idx of the new player cell
    int checkNewCell(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int pIdxCell);  

    bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xMovement, int yMovement, int direction, int idxCell);
};

// function reads out values in that form for each row: x,y,width,height (if a row does not posses that structure, it gets skipped) ; used in assignObject()
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
        // extract numbers separated by a comma
        while (std::getline(ss, number, ',')) {
            try {
                numbers.push_back(std::stoi(number));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Fehler: Ungültige Zahl in der Zeile \"" << line << "\"" << std::endl;
                break;
            }
        }

        // check if actually four numbers were recognized
        if (numbers.size() == 4) {
            result.push_back(numbers);
        } else {
            std::cerr << "Warnung: Zeile ignoriert, da sie keine 4 Zahlen enthält: \"" << line << "\"" << std::endl;
        }
    }

    file.close();
    return result;
}
