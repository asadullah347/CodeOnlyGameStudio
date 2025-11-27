#include <iostream>
using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char currentPlayer = 'X';


void printBoard() {
    cout << "Tic Tac Toe Game" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isWinner(char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}
bool isDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    int move;
    while (true) {
        printBoard();
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;
        if (move < 1 || move > 9) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Cell already taken. Try again." << endl;
            continue;
        }
        board[row][col] = currentPlayer;
        if (isWinner(currentPlayer)) {
            printBoard();
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }
        if (isDraw()) {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }
        switchPlayer();
    }
    return 0;
}