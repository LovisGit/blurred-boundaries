class Player {

private:
    char _walkingDirection; //vielleicht mit wasd als char Wert?
    int _xCoordinate;
    int _yCoordinate;

public:
    Player();

    int getXCoordinate() const;
    int getYCoordinate() const;

    void setXCoordinate(int xCoordinate);
    void setYCoordinate(int yCoordinate);

};