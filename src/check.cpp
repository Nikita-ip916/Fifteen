#include <iostream>
using namespace std;

bool checkToWin(int** gameBoard, const int boardSize)
{
    bool isCorrect = true;
    int expBoard[boardSize][boardSize];
    int num = 1;
    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            if (num != 16)
                expBoard[i][j] = num;
            else
                expBoard[i][j] = 0;
            num++;
        }
    }

    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            if (isCorrect) {
                if (gameBoard[i][j] != expBoard[i][j])
                    isCorrect = false;
            }
        }
    }
    return isCorrect;
}
