#include <iostream>
using namespace std;

void outArray(int** gameBoard, int boardSize)
{
    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            cout << gameBoard[i][j] << " ";
        }
        cout << endl;
    }
}
