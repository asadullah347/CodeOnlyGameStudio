#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;


bool gameOver;

const int width = 20;
const int height = 20;

// Snake head position
int x, y;
// Fruit position
int fruitX, fruitY;
int score;

// Direction enumeration
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//explain enum here
// The eDirection enum is used to represent the possible directions the snake can move in the game.



void SetUp()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}


void Draw()
{
    system("cls"); // to clear the console


    for (int i = 0; i < width + 2; i++)   // Top walls
        cout << "#";
    cout << endl;


    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // Left wall

                if(i == y && j == x)
                    cout << "O"; // Snake head
                else if (i == fruitY && j == fruitX)
                    cout << "F"; // Fruit
                else

                cout << " "; // empty space

            if (j == width - 1)
                cout << "#"; // Right wall

        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)   // Bottom walls
        cout << "#";
    cout << endl;

    // Display score
    cout << "Score: " << score << endl;
}

void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}

void Logic()
{
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Collision with walls
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;
    // Collision with fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    
}



int main() 
{
    SetUp();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
}
