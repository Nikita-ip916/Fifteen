#include <iostream>
using namespace std;
const int n = 5;

int checkToWin(int** gameBoard, int n)
{
    bool isCorrect = true;
    int expBoard[n][n];
    int num = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (num != 16)
                expBoard[i][j] = num;
            else
                expBoard[i][j] = 0;
            num++;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (isCorrect) {
                if (gameBoard[i][j] != expBoard[i][j])
                    isCorrect = false;
            }
        }
    }
    return isCorrect;
}
