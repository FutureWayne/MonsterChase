#pragma once
const int GRID_SIZE = 20;

class Pawn {
protected:
    int x, y;
    char symbol;
    char* name;

public:
    Pawn(int iniX, int iniY, char* name);
    ~Pawn();

    int getX() const;
    int getY() const;
    char getSymbol() const;
    const char* getName() const;
    void SetName(const char* newName);
    void SetPosition(int x, int y);
};