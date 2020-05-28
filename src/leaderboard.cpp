#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define nameflag (result.name.length() > 2 && result.name.length() < 11)
using namespace std;
struct Result {
    string name;
    int hours;
    int minutes;
    int seconds;
};

void clearFile()
{
    ofstream file("records.txt", ofstream::out);
    file << "";
    file.close();
}
bool checkName(Result& result)
{
    bool isCorrect = true;
    if (!nameflag) {
        isCorrect = false;
    }
    if (isCorrect) {
        for (int i = 0; i < int(result.name.length()); i++) {
            if (isCorrect) {
                if (!((int(result.name[i]) > 47 && int(result.name[i]) < 58)
                      || (int(result.name[i]) > 64 && int(result.name[i]) < 91)
                      || (int(result.name[i]) > 96
                          && int(result.name[i]) < 123))) {
                    isCorrect = false;
                }
            }
        }
    }
    return isCorrect;
}
bool isNumber(string str)
{
    bool isNumberFlag = true;
    for (int i = 0; i < (int)str.length(); i++) {
        if (isNumberFlag) {
            if (!(str[i] > 47 && str[i] < 58)) {
                isNumberFlag = false;
            }
        }
    }
    return isNumberFlag;
}
int countStr(Result& result)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    int countOfStr = 0;
    bool isCorrectResult = true;
    string str;
    while (!records.eof()) {
        isCorrectResult = true;
        getline(records, result.name, ' ');
        if (!checkName(result)) {
            isCorrectResult = false;
        }
        str.clear();
        getline(records, str, ' ');
        if (isCorrectResult) {
            if (!isNumber(str)) {
                isCorrectResult = false;
            } else {
                result.hours = atoi(str.c_str());
            }
            str.clear();
            getline(records, str, ' ');
            if (isCorrectResult) {
                if (!isNumber(str)) {
                    isCorrectResult = false;
                } else {
                    result.minutes = atoi(str.c_str());
                }
                str.clear();
                getline(records, str, '\n');
                if (isCorrectResult) {
                    if (!isNumber(str)) {
                        isCorrectResult = false;
                    } else {
                        result.seconds = atoi(str.c_str());
                    }
                }
            }
        } else {
            str.clear();
            getline(records, str, '\n');
        }
        if (isCorrectResult)
            countOfStr++;
    }
    records.close();
    return --countOfStr;
}
void readResult(Result& result, vector<Result>& vector_result)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    bool isCorrectResult = true;
    string str;
    while (!records.eof()) {
        isCorrectResult = true;
        getline(records, result.name, ' ');
        if (!checkName(result)) {
            isCorrectResult = false;
        }
        str.clear();
        getline(records, str, ' ');
        if (isCorrectResult) {
            if (!isNumber(str)) {
                isCorrectResult = false;
            } else {
                result.hours = atoi(str.c_str());
            }
            str.clear();
            getline(records, str, ' ');
            if (isCorrectResult) {
                if (!isNumber(str)) {
                    isCorrectResult = false;
                } else {
                    result.minutes = atoi(str.c_str());
                }
                str.clear();
                getline(records, str, '\n');
                if (isCorrectResult) {
                    if (!isNumber(str)) {
                        isCorrectResult = false;
                    } else {
                        result.seconds = atoi(str.c_str());
                    }
                }
            }
        } else {
            str.clear();
            getline(records, str, '\n');
        }
        if (isCorrectResult)
            vector_result.push_back(result);
    }
    records.close();
}
void getResult(int* time, Result& result, vector<Result>& vector_result)
{
    fstream records(
            "records.txt",
            fstream::app | fstream::binary | fstream::out | fstream::in);
    if (records) {
        result.name = "JustBufferOfName";
        while (!checkName(result)) {
            cout << "Enter your name: ";
            getline(cin, result.name);
            if (!checkName(result))
                cout << "\nName does not match:\nLength of at least 3 and "
                        "no "
                        "more than 10 characters, only numbers and letters "
                        "of "
                        "the Latin alphabet!\n";
        }
        result.seconds = time[0];
        result.minutes = time[1];
        result.hours = time[2];
        records << result.name << " " << result.hours << " " << result.minutes
                << " " << result.seconds << '\n';
    } else {
        cout << "\nFile not found.\n";
    }
    records.close();
}

void sortResult(int* index_array, vector<Result>& vector_result, int length)
{
    int k = 0;
    for (int i = 0; i < length; i++) {
        k = i;
        for (int j = i; j < length; j++) {
            if (vector_result[index_array[k]].hours
                > vector_result[index_array[j]].hours)
                k = j;
            else if (
                    vector_result[index_array[k]].hours
                    == vector_result[index_array[j]].hours) {
                if (vector_result[index_array[k]].minutes
                    > vector_result[index_array[j]].minutes)
                    k = j;
                else if (
                        vector_result[index_array[k]].minutes
                        == vector_result[index_array[j]].minutes) {
                    if (vector_result[index_array[k]].seconds
                        > vector_result[index_array[j]].seconds)
                        k = j;
                }
            }
        }
        swap(index_array[i], index_array[k]);
    }
}

void writeResult(Result& result, vector<Result>& vector_result)
{
    readResult(result, vector_result);
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    int length = vector_result.size();
    int* index_array = new int[length];
    for (int i = 0; i < length; i++) {
        index_array[i] = i;
    }
    sortResult(index_array, vector_result, length);
    records.close();
    clearFile();
    ofstream newrecords("records.txt", ofstream::out);
    if (vector_result.size() > 5) {
        length = 5;
    }
    bool isInLeaderboard = false;
    // Since the top 5 results will be displayed,
    // it makes no sense to store the rest.
    for (int i = 0; i < length; i++) {
        newrecords << vector_result[index_array[i]].name << " "
                   << vector_result[index_array[i]].hours << " "
                   << vector_result[index_array[i]].minutes << " "
                   << vector_result[index_array[i]].seconds << '\n';
        if ((vector_result[index_array[i]].name == result.name)
            && (vector_result[index_array[i]].hours == result.hours)
            && (vector_result[index_array[i]].minutes == result.minutes)
            && (vector_result[index_array[i]].seconds == result.seconds)) {
            isInLeaderboard = true;
        }
    }
    if (isInLeaderboard) {
        cout << "\nYour result hit the table!\nCongratulations!\n";
    } else {
        cout << "\nYour result did not hit the table!\nTry hard next "
                "time!\n";
    }
    delete[] index_array;
    newrecords.close();
    vector_result.clear();
}
void fixFile(Result& result, vector<Result>& vector_result)
{
    vector_result.clear();
    readResult(result, vector_result);
    clearFile();
    int length = vector_result.size();
    int* index_array = new int[length];
    for (int i = 0; i < length; i++) {
        index_array[i] = i;
    }
    sortResult(index_array, vector_result, length);
    if (length > 5) {
        length = 5;
    }
    ofstream newrecords("records.txt", ofstream::out);
    for (int i = 0; i < length; i++) {
        newrecords << vector_result[index_array[i]].name << " "
                   << vector_result[index_array[i]].hours << " "
                   << vector_result[index_array[i]].minutes << " "
                   << vector_result[index_array[i]].seconds << '\n';
    }
    delete[] index_array;
    newrecords.close();
    vector_result.clear();
}
