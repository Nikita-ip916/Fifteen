#include <cstdio>
#include <iostream>
using namespace std;

bool resourseCheck()
{
    FILE* resourse;
    resourse = fopen("Numbers.jpg", "r");
    if (resourse) {
        fclose(resourse);
    } else {
        cout << "Error: Numbers.jpg not found. Exit programm." << endl;
        return false;
    }
    resourse = fopen("Others.jpg", "r");
    if (resourse) {
        fclose(resourse);
    } else {
        cout << "Error: Others.jpg not found. Exit programm." << endl;
        return false;
    }
    resourse = fopen("TimesNewRoman.ttf", "r");
    if (resourse) {
        fclose(resourse);
        return true;
    } else {
        cout << "Error: TimesNewRoman.ttf not found. Exit programm." << endl;
        return false;
    }
}