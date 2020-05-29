#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

int checkGeneration(int** gameBoard, const int boardSize)
{
    int chaosIndex = 0, index = 0;
    int* duplicate = new int[16];

    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            duplicate[index++] = gameBoard[i][j];
        }
    }
    for (int i = 0; i < 16; i++) {
        if (duplicate[i]) {
            for (int j = 0; j < i; j++) {
                if (duplicate[j] > duplicate[i]) {
                    chaosIndex++;
                }
            }
        }
    }
    for (int i = 0; i < 16; ++i) {
        if (duplicate[i] == 0) {
            chaosIndex += 1 + i / 4;
        }
    }

    delete[] duplicate;
    return chaosIndex;
}

void generateArray(int** gameBoard, int boardSize)
{
    int number = 1;
    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            gameBoard[i][j] = number;
            if (number++ == 16) {
                gameBoard[i][j] = 0;
            }
        }
    }

    int firstIndex, secondIndex;
    do {
        for (int i = 1; i < boardSize; i++) {
            for (int j = 1; j < boardSize; j++) {
                firstIndex = rand() % 4 + 1;
                secondIndex = rand() % 4 + 1;
                swap(gameBoard[i][j], gameBoard[firstIndex][secondIndex]);
            }
        }
    } while (checkGeneration(gameBoard, boardSize) % 2 != 0);
}
