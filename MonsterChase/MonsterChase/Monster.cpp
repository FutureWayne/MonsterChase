#include "Monster.h"
#include <stdlib.h>

void Monster::moveMonsterToPlayer(const Pawn& player)
{
    const int playerX = player.getX();
    const int playerY = player.getY();
    
    // Lambda for moving along X
    auto moveAlongX = [&]() {
        x += (x < playerX) ? 1 : -1;
    };

    // Lambda for moving along Y
    auto moveAlongY = [&]() {
        y += (y < playerY) ? 1 : -1;
    };

    // Randomly decide to move in x or y axis
    const bool moveInX = rand() % 2;

    if (moveInX) {
        (x != playerX) ? moveAlongX() : moveAlongY();
    }
    else {
        (y != playerY) ? moveAlongY() : moveAlongX();
    }
}
