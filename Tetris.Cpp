#include <iostream>
using namespace std;


const int rows = 20; //Height of the board
const int columns = 10; //Width of the board
int board[rows][columns]; //Represented as a 2D array. empty (0) or occupied (1)



void PrintBoard() {
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(board[i][j] == 0)
                cout << "."; // Empty cell
            else
            cout << board[i][j] << " "; //filled cell
        }
        cout << endl;
    }
}

int main()
{    
    // Initialize the board to empty
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;
        }
    }

    PrintBoard();
    return 0;
}