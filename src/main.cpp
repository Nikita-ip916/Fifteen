#include "gen.cpp"
#include "out.cpp"
#include <ctime>
#include <iostream>
const int n = 5;
using namespace std;
#define DEBUG

int main()
{
    srand(time(0));

    int** arr = new int*[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];
    generateArray(arr, n);
#ifdef DEBUG
    outArray(arr, n);
#endif
    cout << endl;
}
