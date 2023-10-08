#pragma once
#include "Vector2D.h"

const int GRID_SIZE = 20;

class Pawn {
protected:
    Vector2D position;
    char symbol;
    char* name;

public:
    Pawn(Vector2D iniPosition, char* name);
    ~Pawn();

    Vector2D getPosition() const;
    char getSymbol() const;
    const char* getName() const;
    void SetName(const char* newName);
    void SetPosition(Vector2D newPosition);
};