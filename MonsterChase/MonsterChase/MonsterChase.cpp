#include <conio.h>  // For _getch()
#include <iostream>

#include "Monster.h"
#include "Player.h"
using namespace std;


void clearGrid(char grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++) 
    {
        for (int j = 0; j < GRID_SIZE; j++) 
        {
            grid[i][j] = ' ';
        }
    }
}

void displayGrid(char grid[GRID_SIZE][GRID_SIZE], Player* player, Monster** monstersPtr, const int num_monsters)
{
    system("cls");
    clearGrid(grid);

    grid[player->getY()][player->getX()] = player->getSymbol();
    for (int i = 0; i < num_monsters; i++)
    {
        grid[monstersPtr[i]->getY()][monstersPtr[i]->getX()] = monstersPtr[i]->getSymbol();
    }

    for (int i = 0; i < GRID_SIZE; i++) 
    {
        for (int j = 0; j < GRID_SIZE; j++) 
        {
            cout << '|' << grid[i][j];
        }
        cout << "|\n";
    }

    // Display player's details
    std::cout << "Player: " << player->getName() << " at (" << player->getX() << ", " << player->getY() << ")" << std::endl;

    // Display monstersPtr' details
    for (int i = 0; i < num_monsters; i++) {
        std::cout << "Monster: " << monstersPtr[i]->getName() << " at (" << monstersPtr[i]->getX() << ", " << monstersPtr[i]->getY() << ")" << std::endl;
    }
}


bool checkCollision(const Pawn& pawn1, const Pawn& pawn2)
{
    int xDiff = abs(pawn1.getX() - pawn2.getX());
    int yDiff = abs(pawn1.getY() - pawn2.getY());

    // Directly next to each other or on top of each other
    return (xDiff <= 1 && yDiff <= 1);
}


int main()
{
    char grid[GRID_SIZE][GRID_SIZE];
	char tempName[256];
    int num_monsters;
    
    
    cout << "Enter your name: ";
    cin.getline(tempName, 256);
    Player* player = new Player(GRID_SIZE / 2, GRID_SIZE / 2, tempName);

    // Initializing monstersPtr
    cout << "Enter the number of monstersPtr: ";
    cin >> num_monsters;
    while (num_monsters < 0 || num_monsters > 50) {
        cout << "Invalid number. Please enter between 0 and 50: ";
        cin >> num_monsters;
    }
    cin.ignore(1024, '\n');  // Clearing the input buffer
    Monster** monstersPtr = new Monster*[num_monsters];
    for (int i = 0; i < num_monsters; i++) 
    {
        cout << "Enter name for monster " << (i + 1) << ": ";
        cin.getline(tempName, 256);
        int initX = rand() % GRID_SIZE;
        int initY = rand() % GRID_SIZE;
        monstersPtr[i] = new Monster(initX, initY, tempName);
    }


    while (true) 
    {
        // Display grid
        displayGrid(grid, player, monstersPtr, num_monsters);

        // Getting player input
        char input = _getch();
        if (input == 'Q' || input == 'q')
        {
            break;
        }

        player->movePlayerByInput(input);

        // Updating monsters positions
        for (int i = 0; i < num_monsters; i++)
        {
            monstersPtr[i]->moveMonsterToPlayer(*player);
        }

        // After updating player's position
        for (int i = 0; i < num_monsters; i++) 
        {
            if (checkCollision(*player, *monstersPtr[i])) 
            {

                displayGrid(grid, player, monstersPtr, num_monsters);

                std::cout << "*******************************************" << std::endl;
                std::cout << "Player collided with a monster! Game over." << std::endl;
                std::cout << "*******************************************" << std::endl;
                delete player;
                return 0;
            }
        }

        // Updating monstersPtr' positions and checking for Monster-Monster collision
        for (int i = 0; i < num_monsters; i++) 
        {
            for (int j = i + 1; j < num_monsters; j++) 
            {
                if (checkCollision(*monstersPtr[i], *monstersPtr[j])) 
                {
                    // Free the memory for the monsters
                    delete monstersPtr[i];
                    delete monstersPtr[j];

                    monstersPtr[i] = monstersPtr[num_monsters - 1];  // Move the last monster to the ith position
                    monstersPtr[j] = monstersPtr[num_monsters - 2];  // Move the second last monster to the jth position

                    num_monsters -= 2;  // Two monstersPtr are removed

                    // Adjust loop counters since monstersPtr have shifted
                    i--;
                    break;  // One monster can collide with only one other monster in one move
                }
            }
        }
    }

    delete player;

    return 0;
}
