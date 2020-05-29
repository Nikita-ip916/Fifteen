#include <iostream>
using namespace std;
void changeTimeDigits(int* time)
{
    if (time[0] < 0 || time[1] < 0 || time[2] < 0) {
        time[0] = time[1] = time[2] = 0;
        cout << "\nError: negative time. Time reload.\n";
    }
    if (time[0] > 60 || time[1] > 59 || time[2] > 23) {
        time[0] = time[1] = time[2] = 0;
        cout << "\nError: Time out of range. Time reload.\n";
    }
    if (time[0] > 59) {
        time[0] = 0;
        time[1]++;
    }
    if (time[1] > 59) {
        time[1] = 0;
        time[2]++;
    }
    if (time[2] > 23) {
        time[2] = 0;
    }
}
