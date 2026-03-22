#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <thread> // For std::this_thread::sleep_for
#include <chrono>
#include <windows.h>
using namespace std;


bool gameOver;

const int width = 20;
const int height = 20;

// Snake head position
int x, y;
int tailX[100], tailY[100];
int nTail; // tail length, not used in this simple version
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
    //system("cls"); // to clear the console
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0}); //to clear the console without flickeringz


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
                {   // Snake tail logic
                    bool printTail = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o"; // Snake tail
                            printTail = true;
                        }
                    }
                    if (!printTail)
                        cout << " "; // empty space

                }
                
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
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    //get the previous position of the head and store it in the first tail segment
    tailX[0] = x; 
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

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
    /* if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true; */

    //to make the snake pass through walls and appear on the opposite side
    if (x >= width) x = 0; else if (x < 0) x = width -1;
    if (y >= height) y = 0; else if (y < 0) y = height -1;


    // Collision with tail
    for(int i =0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Collision with fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; // increase tail length
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
        Sleep(100); //sleep(10) for faster speed
    }
}
