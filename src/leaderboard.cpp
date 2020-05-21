#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define nameflag (result.name.length() > 2 && result.name.length() < 11)
using namespace std;
const char new_string = '\n';
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

int countStr()
{
    ifstream records("records.txt");
    int countOfStr = 0;
    char* bufferLine = new char[500];
    while (records) {
        records.getline(bufferLine, 500);
        countOfStr++;
    }
    delete[] bufferLine;
    records.close();
    return --countOfStr; // Убираем фактически пустую строку.
}

void getResult(int* time, Result& result, vector<Result> vector_result)
{
    fstream records(
            "records.txt",
            ios::app | fstream::binary | fstream::out | fstream::in);
    if (records) {
        result.name = "JustBufferOfName";
        while (!nameflag) {
            cout << "Введите имя: ";
            cin >> result.name;
            if (!nameflag)
                cout << "\nИмя не подходит под условия:\nДлина не менее 3 и не "
                        "более 10 символов!\n";
        }
        result.seconds = time[0];
        result.minutes = time[1];
        result.hours = time[2];
        records << result.name << " " << result.hours << " " << result.minutes
                << " " << result.seconds << '\n';
    } else {
        cout << "\nФайл не найден.\n";
    }
    records.close();
}

void sortResult(int* index_array, vector<Result> vector_result, int length)
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

void writeResult(Result& result, vector<Result> vector_result)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    for (int i = 0; i < countStr(); i++) {
        records >> result.name >> result.hours >> result.minutes
                >> result.seconds;
        vector_result.push_back(result);
    }
    int length = vector_result.size();
    int* index_array = new int[length];
    for (int i = 0; i < length; i++) {
        index_array[i] = i;
    }

    sortResult(index_array, vector_result, length);
    records.close();
    clearFile();
    ofstream newrecords("records.txt", ofstream::out);
    if (vector_result.size() > 5)
        length = 5;
    // Так как отображаться будут 5 лучших результатов,
    // то смысла хранить остальные - нет.
    for (int i = 0; i < length; i++) {
        newrecords << vector_result[index_array[i]].name << " "
                   << vector_result[index_array[i]].hours << " "
                   << vector_result[index_array[i]].minutes << " "
                   << vector_result[index_array[i]].seconds << '\n';
    }
    newrecords.close();
    vector_result.clear();
}

void showResult(Result& result, vector<Result> vector_result)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    for (int i = 0; i < countStr(); i++) {
        records >> result.name >> result.hours >> result.minutes
                >> result.seconds;
        vector_result.push_back(result);
    }
    records.close();
    int length = vector_result.size();
    for (int i = 0; i < length; i++) {
        cout << i + 1 << ". " << vector_result[i].name << " - "
             << vector_result[i].hours << ":" << vector_result[i].minutes << ":"
             << vector_result[i].seconds << endl;
    }
    vector_result.clear();
}
