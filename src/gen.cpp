#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

/*
 * Задача Лойда описывается в checkGeneration();
 *
 * Данная функция проверит сгенерированную матрицу чисел и вернёт
 * индекс хаотичности (он же параметр беспорядка).
 * Чётный параметр - ряд решается, иначе нет и будет генерировать
 * повторно, пока не будет решаться.
 */

int checkGeneration(int** gameBoard, const int boardSize)
{
    int chaos_index = 0, index = 0;
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
                    chaos_index++;
                }
            }
        }
    }
    for (int i = 0; i < 16; ++i) {
        if (duplicate[i] == 0) {
            chaos_index += 1 + i / 4;
        }
    }

    delete[] duplicate;
    return chaos_index;
}

void generateArray(int** gameBoard, int boardSize)
{
    int c = 1;
    for (int i = 1; i < boardSize; i++) {
        for (int j = 1; j < boardSize; j++) {
            gameBoard[i][j] = c;
            if (c++ == 16) {
                gameBoard[i][j] = 0;
            }
        }
    }

    int a, b;
    do {
        for (int i = 1; i < boardSize; i++) {
            for (int j = 1; j < boardSize; j++) {
                a = rand() % 4 + 1;
                b = rand() % 4 + 1;
                swap(gameBoard[i][j], gameBoard[a][b]);
            }
        }
    } while (checkGeneration(gameBoard, boardSize) % 2 != 0);
}
