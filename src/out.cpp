#include <iostream>
using namespace std;

void outArray(int** matrix, int n)
{
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
