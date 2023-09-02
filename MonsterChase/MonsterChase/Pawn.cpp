#include "Pawn.h"
#include <string.h>

Pawn::Pawn(int iniX, int iniY, char* name)
{
    this->x = iniX;
    this->y = iniY;
    this->symbol = ' ';

    SetName(name);
}

Pawn::~Pawn()
{
    delete[] name;
}

int Pawn::getX() const {
    return x;
}

int Pawn::getY() const {
    return y;
}

char Pawn::getSymbol() const {
    return symbol;
}

const char* Pawn::getName() const {
    return name;
}

void Pawn::SetName(const char* newName)
{
	delete[] name;

	size_t length = strlen(newName);
    char* nameMemory = new char[length + 1];// +1 for null terminator
    strncpy_s(nameMemory, length + 1, newName, length);
    name = nameMemory;
}

void Pawn::SetPosition(int tarX, int tarY)
{
    x = tarX;
    y = tarY;
}
