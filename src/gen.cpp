#include <cmath>
#include <iostream>
using namespace std;

void generateArray(int** matr, int n)
{
    int c = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            matr[i][j] = c;
            if (c++ == 16)
                matr[i][j] = 0;
        }
    }

    int a, b;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            a = rand() % 4 + 1;
            b = rand() % 4 + 1;
            swap(matr[i][j], matr[a][b]);
        }
    }
}
