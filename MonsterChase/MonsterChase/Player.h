#pragma once
#include "Pawn.h"

class Player : public Pawn {
public:
    Player(Vector2D initPosition, char* initName) : Pawn(initPosition, initName) {
        symbol = 'P';
    }


    void movePlayerByInput(char direction);
};
