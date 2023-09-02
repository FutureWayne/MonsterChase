#pragma once
#include "Pawn.h"

class Player : public Pawn {
public:
    Player(int initX, int initY, char* initName) : Pawn(initX, initY, initName) {
        symbol = 'P';
    }


    void movePlayerByInput(char direction);
};
