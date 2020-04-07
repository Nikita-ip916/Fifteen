#include <iostream>
using namespace std;

void generateArray(int** matr, int n)
{
    int a, b;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            matr[i][j] = 0;
        }
    }
    for (int i = 1; i < 16; i++) {
        do {
            a = rand() % 4 + 1;
            b = rand() % 4 + 1;
        } while (matr[a][b] != 0);
        matr[a][b] = i;
    }
}
