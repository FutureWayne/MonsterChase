#pragma once
#include "Pawn.h"

class Monster : public Pawn {
public:
    Monster(Vector2D initPosition, char* initName) : Pawn(initPosition, initName) {
        symbol = 'M';
    }

    void moveMonsterToPlayer(const Pawn& player);
};
