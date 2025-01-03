#include <vector>
#include <set>
#include "Object.hpp"
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ObjectAdministrator{                          //Ich habe wohl die Bedeutungen von row und column vertauscht, naja...

private:
    
 int _rowSize;              
 int _columnSize;

 int _anzRowsPerColumn;


 struct Zelle{                                                          //Die Map wird in viele gleichgroße Zellen aufgeteilt die Informationen wie die Objekte innerhalb der Zelle beinhaltet, um das zu checken der Kollision lokal zu erlauben         

  int _xZellenPos;
  int _yZellenPos;

  std::set<Object> _surroundingObjects;

  Zelle();  //Wegen dem Compiler....
  
  Zelle(int xPos, int yPos);
  void addObject(const Object& neuesObjekt);                           //inserted in _surroundingObjects ein neues Objekt                  
};


 std::vector<Zelle> _dasGrid;
 
 void assignObjects();                                                //fügt den erzeugten Zellen ihre Objekte zu je nach angegebenen Koordinaten 

 int neueZelleErreicht(int idxVorher, int richtung);                 //gibt einem die indexe der Zelle aus, wenn man in eine neue Eintritt

 std::vector<int> felderZuPruefen(int idxVorher, int richtung);      //Gedacht für die CheckCollision, wählt die zugeprüfenden Zelle aus je nach Richtung

 bool checkOverlap(const Zelle& zelle, int posX, int posY, int width, int height);    //Für assignObject, hilft für einen besseren Überblick des Codes

public:

 ObjectAdministrator(int windowHeight, int windowWidht, int anzColumns, int anzRows, int playerXPos, int playerYPos, int& startZelle);  //aufgerufen von externer Klasse

 ObjectAdministrator();

 int checkNeueZelle(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int pIdxZelle);  //schaut ob der Spieler vollkommen in eine neue Zelle eindringt, wenn ja wird geupdatet

 bool checkCollision(int playerXPos, int playerYPos, int playerWidht, int playerHeight, int xBewegung, int yBewegung, int richtung, int idxZelle);  //selbsterklärend

};

inline std::vector<std::vector<int>> readObjectsFromFile(const std::string& filename) {         //Funktion liest aus einer Textdatei, hier Werte.txt, eine Zeile aus (in folgender Form: x,y,width,height), um diese in ein Feld zu posten und diese auszugeben, verwendet in assignObject()
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
