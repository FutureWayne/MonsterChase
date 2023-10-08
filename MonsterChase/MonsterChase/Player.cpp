#include "Player.h"

void Player::movePlayerByInput(const char direction)
{
    switch (direction)
    {
    case 'W':
    case 'w':
        if (position.y > 0)
        {
            position += Vector2D(0, -1); // Up
        }
        break;

    case 'A':
    case 'a':
        if (position.x > 0)
        {
            position += Vector2D(-1, 0); // Left
        }
        break;

    case 'S':
    case 's':
        if (position.y < GRID_SIZE - 1)
        {
            position += Vector2D(0, 1); // Down
        }
        break;

    case 'D':
    case 'd':
        if (position.x < GRID_SIZE - 1)
        {
            position += Vector2D(1, 0); // Right
        }
        break;

    default:;
    }
}
