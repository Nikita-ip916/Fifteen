#include <iostream>
using namespace std;
void stopWatch(int* t)
{
    if (t[0] < 0 || t[1] < 0 || t[2] < 0) {
        t[0] = t[1] = t[2] = 0;
        cout << "\nError: negative time. Time reload." << endl;
    }
    if (t[0] > 60 || t[1] > 59 || t[2] > 23) {
        t[0] = t[1] = t[2] = 0;
        cout << "\nError: Time out of range. Time reload." << endl;
    }
    if (t[0] > 59) {
        t[0] = 0;
        t[1]++;
    }
    if (t[1] > 59) {
        t[1] = 0;
        t[2]++;
    }
    if (t[2] > 23) {
        t[2] = 0;
    }
}