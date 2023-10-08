#include <conio.h>  // For _getch()
#include <iostream>

#include "Monster.h"
#include "Player.h"
#include "Vector2D.h"
#include "Vector2DUnitTest.h"
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

    grid[player->getPosition().y][player->getPosition().x] = player->getSymbol();
    for (int i = 0; i < num_monsters; i++)
    {
        grid[monstersPtr[i]->getPosition().y][monstersPtr[i]->getPosition().x] = monstersPtr[i]->getSymbol();
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
    std::cout << "Player: " << player->getName() << " at (" << player->getPosition().x << ", " << player->getPosition().y << ")" << std::endl;

    // Display monstersPtr' details
    for (int i = 0; i < num_monsters; i++) {
        std::cout << "Monster: " << monstersPtr[i]->getName() << " at (" << monstersPtr[i]->getPosition().x << ", " << monstersPtr[i]->getPosition().y << ")" << std::endl;
    }
}


bool checkCollision(const Pawn& pawn1, const Pawn& pawn2)
{
    Vector2D diff = pawn1.getPosition() - pawn2.getPosition();
    return (abs(diff.x) <= 1 && abs(diff.y) <= 1);
}


int main()
{
    Vector2DUnitTest();


    char grid[GRID_SIZE][GRID_SIZE];
	char tempName[256];
    int num_monsters;
    
    
    cout << "Enter your name: ";
    cin.getline(tempName, 256);
    Player* player = new Player(Vector2D(GRID_SIZE / 2, GRID_SIZE / 2), tempName);

    // Initializing monstersPtr
    cout << "Enter the number of monsters: ";
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
        monstersPtr[i] = new Monster(Vector2D(initX, initY), tempName);
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
