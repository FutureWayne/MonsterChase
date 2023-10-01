#include "Player.h"

void Player::movePlayerByInput(const char direction)
{
    switch (direction)
    {
    case 'W':
    case 'w':
        if (y > 0)
        {
            y--;
        }
        break;

    case 'A':
    case 'a':
        if (x > 0)
        {
            x--;
        }
        break;

    case 'S':
    case 's':
        if (y < GRID_SIZE - 1)
        {
            y++;
        }
        break;

    case 'D':
    case 'd':
        if (x < GRID_SIZE - 1)
        {
            x++;
        }
        break;

    default:;
    }
}
