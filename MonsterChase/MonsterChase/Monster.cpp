#include "Monster.h"
#include <stdlib.h>

void Monster::moveMonsterToPlayer(const Pawn& player)
{
    const Vector2D playerPosition = player.getPosition();
    
    // Lambda for moving along X
    auto moveAlongX = [&]() {
        position.x += (position.x < playerPosition.x) ? 1 : -1;
    };

    // Lambda for moving along Y
    auto moveAlongY = [&]() {
        position.y += (position.y < playerPosition.y) ? 1 : -1;
    };

    // Randomly decide to move in x or y axis
    const bool moveInX = rand() % 2;

    if (moveInX) {
        (position.x != playerPosition.x) ? moveAlongX() : moveAlongY();
    }
    else {
        (position.y != playerPosition.y) ? moveAlongY() : moveAlongX();
    }
}
