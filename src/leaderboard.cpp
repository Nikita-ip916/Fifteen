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
    string buffer;
    while (!records.eof()) {
        isCorrectResult = true;
        getline(records, result.name, ' ');
        if (!checkName(result)) {
            isCorrectResult = false;
        }
        buffer.clear();
        getline(records, buffer, ' ');
        if (isCorrectResult) {
            if (!isNumber(buffer)) {
                isCorrectResult = false;
            } else {
                result.hours = atoi(buffer.c_str());
                if (result.hours > 23) {
                    isCorrectResult = false;
                }
            }
            buffer.clear();
            getline(records, buffer, ' ');
            if (isCorrectResult) {
                if (!isNumber(buffer)) {
                    isCorrectResult = false;
                } else {
                    result.minutes = atoi(buffer.c_str());
                    if (result.minutes > 59) {
                        isCorrectResult = false;
                    }
                }
                buffer.clear();
                getline(records, buffer, '\n');
                if (isCorrectResult) {
                    if (!isNumber(buffer)) {
                        isCorrectResult = false;
                    } else {
                        result.seconds = atoi(buffer.c_str());
                        if (result.seconds > 59) {
                            isCorrectResult = false;
                        }
                    }
                }
            }
        } else {
            buffer.clear();
            getline(records, buffer, '\n');
        }
        if (isCorrectResult)
            countOfStr++;
    }
    records.close();
    return --countOfStr;
}
void readResult(Result& result, vector<Result>& vectorResult)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    bool isCorrectResult = true;
    string buffer;
    while (!records.eof()) {
        isCorrectResult = true;
        getline(records, result.name, ' ');
        if (!checkName(result)) {
            isCorrectResult = false;
        }
        buffer.clear();
        getline(records, buffer, ' ');
        if (isCorrectResult) {
            if (!isNumber(buffer)) {
                isCorrectResult = false;
            } else {
                result.hours = atoi(buffer.c_str());
                if (result.hours > 23) {
                    isCorrectResult = false;
                }
            }
            buffer.clear();
            getline(records, buffer, ' ');
            if (isCorrectResult) {
                if (!isNumber(buffer)) {
                    isCorrectResult = false;
                } else {
                    result.minutes = atoi(buffer.c_str());
                    if (result.minutes > 59) {
                        isCorrectResult = false;
                    }
                }
                buffer.clear();
                getline(records, buffer, '\n');
                if (isCorrectResult) {
                    if (!isNumber(buffer)) {
                        isCorrectResult = false;
                    } else {
                        result.seconds = atoi(buffer.c_str());
                        if (result.seconds > 59) {
                            isCorrectResult = false;
                        }
                    }
                }
            }
        } else {
            buffer.clear();
            getline(records, buffer, '\n');
        }
        if (isCorrectResult)
            vectorResult.push_back(result);
    }
    records.close();
}
void getResult(int* time, Result& result)
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

void sortResult(int* indexArray, vector<Result>& vectorResult, int length)
{
    int indexToSwap = 0;
    for (int i = 0; i < length; i++) {
        indexToSwap = i;
        for (int j = i; j < length; j++) {
            if (vectorResult[indexArray[indexToSwap]].hours
                > vectorResult[indexArray[j]].hours)
                indexToSwap = j;
            else if (
                    vectorResult[indexArray[indexToSwap]].hours
                    == vectorResult[indexArray[j]].hours) {
                if (vectorResult[indexArray[indexToSwap]].minutes
                    > vectorResult[indexArray[j]].minutes)
                    indexToSwap = j;
                else if (
                        vectorResult[indexArray[indexToSwap]].minutes
                        == vectorResult[indexArray[j]].minutes) {
                    if (vectorResult[indexArray[indexToSwap]].seconds
                        > vectorResult[indexArray[j]].seconds)
                        indexToSwap = j;
                }
            }
        }
        swap(indexArray[i], indexArray[indexToSwap]);
    }
}

void writeResult(Result& result, vector<Result>& vectorResult)
{
    Result currentResult;
    currentResult.name = result.name;
    currentResult.hours = result.hours;
    currentResult.minutes = result.minutes;
    currentResult.seconds = result.seconds;
    readResult(result, vectorResult);
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    int length = vectorResult.size();
    int* indexArray = new int[length];
    for (int i = 0; i < length; i++) {
        indexArray[i] = i;
    }
    sortResult(indexArray, vectorResult, length);
    records.close();
    clearFile();
    ofstream newrecords("records.txt", ofstream::out);
    if (vectorResult.size() > 5) {
        length = 5;
    }
    bool isInLeaderboard = false;
    // Since the top 5 results will be displayed,
    // it makes no sense to store the rest.
    for (int i = 0; i < length; i++) {
        newrecords << vectorResult[indexArray[i]].name << " "
                   << vectorResult[indexArray[i]].hours << " "
                   << vectorResult[indexArray[i]].minutes << " "
                   << vectorResult[indexArray[i]].seconds << '\n';
        if ((vectorResult[indexArray[i]].name == currentResult.name)
            && (vectorResult[indexArray[i]].hours == currentResult.hours)
            && (vectorResult[indexArray[i]].minutes == currentResult.minutes)
            && (vectorResult[indexArray[i]].seconds == currentResult.seconds)) {
            isInLeaderboard = true;
        }
    }
    if (isInLeaderboard) {
        cout << "\nYour result hit the table!\nCongratulations!\n";
    } else {
        cout << "\nYour result did not hit the table!\nTry hard next "
                "time!\n";
    }
    delete[] indexArray;
    newrecords.close();
    vectorResult.clear();
}
void fixFile(Result& result, vector<Result>& vectorResult)
{
    vectorResult.clear();
    readResult(result, vectorResult);
    clearFile();
    int length = vectorResult.size();
    int* indexArray = new int[length];
    for (int i = 0; i < length; i++) {
        indexArray[i] = i;
    }
    sortResult(indexArray, vectorResult, length);
    if (length > 5) {
        length = 5;
    }
    ofstream newrecords("records.txt", ofstream::out);
    for (int i = 0; i < length; i++) {
        newrecords << vectorResult[indexArray[i]].name << " "
                   << vectorResult[indexArray[i]].hours << " "
                   << vectorResult[indexArray[i]].minutes << " "
                   << vectorResult[indexArray[i]].seconds << '\n';
    }
    delete[] indexArray;
    newrecords.close();
    vectorResult.clear();
}
