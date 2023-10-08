#include "Pawn.h"
#include <string.h>


Pawn::Pawn(Vector2D iniPosition, char* name)
{
    this->position = iniPosition;
    this->symbol = ' ';
    SetName(name);
}

Pawn::~Pawn()
{
    delete[] name;
}

Vector2D Pawn::getPosition() const
{
    return position;
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

void Pawn::SetPosition(Vector2D newPosition)
{
    position = newPosition;
}
