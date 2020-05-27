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

int countStr(Result& result)
{
    ifstream records("records.txt");
    int countOfStr = 0;
    while (!records.eof()) {
        records >> result.name >> result.hours >> result.minutes
                >> result.seconds;
        countOfStr++;
    }
    records.close();
    return --countOfStr; // Delete last string if fact
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

void getResult(int* time, Result& result, vector<Result>& vectorResult)
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
                cout << "\nName does not match:\nLength of at least 3 and no "
                        "more than 10 characters, only numbers and letters of "
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
    int k = 0;
    for (int i = 0; i < length; i++) {
        k = i;
        for (int j = i; j < length; j++) {
            if (vectorResult[indexArray[k]].hours
                > vectorResult[indexArray[j]].hours)
                k = j;
            else if (
                    vectorResult[indexArray[k]].hours
                    == vectorResult[indexArray[j]].hours) {
                if (vectorResult[indexArray[k]].minutes
                    > vectorResult[indexArray[j]].minutes)
                    k = j;
                else if (
                        vectorResult[indexArray[k]].minutes
                        == vectorResult[indexArray[j]].minutes) {
                    if (vectorResult[indexArray[k]].seconds
                        > vectorResult[indexArray[j]].seconds)
                        k = j;
                }
            }
        }
        swap(indexArray[i], indexArray[k]);
    }
}

void writeResult(Result& result, vector<Result>& vectorResult)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    for (int i = 0; i < countStr(result); i++) {
        records >> result.name >> result.hours >> result.minutes
                >> result.seconds;
        if (checkName(result)) {
            vectorResult.push_back(result);
        }
    }
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
        if ((vectorResult[indexArray[i]].name == result.name)
            && (vectorResult[indexArray[i]].hours == result.hours)
            && (vectorResult[indexArray[i]].minutes == result.minutes)
            && (vectorResult[indexArray[i]].seconds == result.seconds)) {
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
    vectorResult.clear();
}
void readResult(Result& result, vector<Result>& vectorResult)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    for (int i = 0; i < countStr(result); i++) {
        records >> result.name >> result.hours >> result.minutes
                >> result.seconds;
        vectorResult.push_back(result);
    }
    records.close();
}
void fixFile(Result& result, vector<Result>& vector_result)
{
    vector_result.clear();
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    for (int i = 0; i < countStr(result); i++) {
        records >> result.name >> result.hours >> result.minutes
                >> result.seconds;
        if (checkName(result)) {
            vector_result.push_back(result);
        }
    }
    records.close();
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
