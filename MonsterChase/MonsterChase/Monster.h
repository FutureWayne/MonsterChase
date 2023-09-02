#pragma once
#include "Pawn.h"

class Monster : public Pawn {
public:
    Monster(int initX, int initY, char* initName) : Pawn(initX, initY, initName) {
        symbol = 'M';
    }

    void moveMonsterToPlayer(const Pawn& player);
};
