#include <iostream>
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


    for (int i = 0; i < width+2; i++)   // Top walls
        cout << "#";
    cout << endl;


    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // Left wall

                cout << " "; // empty space

            if (j == width - 1)
                cout << "#"; // Right wall

        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)   // Bottom walls
        cout << "#";
    cout << endl;
}

void Input()
{
    
}

void Logic()
{
    
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
