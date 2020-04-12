#include "gen.h"
#include "out.h"
#include <ctime>
#include <iostream>
const int n = 5;
using namespace std;

int main()
{
    srand(time(0));

    int** arr = new int*[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];
    generateArray(arr, n);
    outArray(arr, n);
    cout << endl;
}
