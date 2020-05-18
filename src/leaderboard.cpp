#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#define nameflag (r.name.length() > 2 && r.name.length() < 11)
using namespace std;
const char ch = '\n';
struct result {
    string name;
    int h;
    int m;
    int s;
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
    int count = 0;
    char* str = new char[500];
    while (records) {
        records.getline(str, 500);
        count++;
    }
    delete[] str;
    records.close();
    return --count; // Убираем фактически пустую строку.
}

void getResult(int* t, result& r, vector<result> vr)
{
    fstream records(
            "records.txt",
            ios::app | fstream::binary | fstream::out | fstream::in);
    if (records) {
        r.name = "JustBufferOfName";
        while (!nameflag) {
            cout << "Введите имя: ";
            cin >> r.name;
            if (!nameflag)
                cout << "\nИмя не подходит под условия:\nДлина не менее 3 и не "
                        "более 10 символов!\n";
        }
        r.h = t[0];
        r.m = t[1];
        r.s = t[2];
        records << r.name << " " << r.h << " " << r.m << " " << r.s << '\n';
    } else {
        cout << "\nФайл не найден.\n";
    }
    records.close();
}

void sortResult(vector<result>& vr, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (vr[j].h > vr[j + 1].h) {
                swap(vr[j].name, vr[j + 1].name);
                swap(vr[j].h, vr[j + 1].h);
                swap(vr[j].m, vr[j + 1].m);
                swap(vr[j].s, vr[j + 1].s);
            } else if (vr[j].h == vr[j + 1].h) {
                if (vr[j].m > vr[j + 1].m) {
                    swap(vr[j].name, vr[j + 1].name);
                    swap(vr[j].h, vr[j + 1].h);
                    swap(vr[j].m, vr[j + 1].m);
                    swap(vr[j].s, vr[j + 1].s);
                } else if (vr[j].m == vr[j + 1].m) {
                    if (vr[j].s > vr[j + 1].s) {
                        swap(vr[j].name, vr[j + 1].name);
                        swap(vr[j].h, vr[j + 1].h);
                        swap(vr[j].m, vr[j + 1].m);
                        swap(vr[j].s, vr[j + 1].s);
                    }
                }
            }
        }
    }
}

void rewriteResult(result& r, vector<result> vr)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    int c = countStr();
    for (int i = 0; i < c; i++) {
        records >> r.name >> r.h >> r.m >> r.s;
        vr.push_back(r);
    }
    sortResult(vr, vr.size());
    records.close();
    clearFile();
    ofstream newrecords("records.txt", ofstream::out);
    int length = vr.size();
    if (vr.size() > 5)
        length = 5;
    // Так как отображаться будут 5 лучших результатов,
    // то смысла хранить остальные - нет.
    for (int i = 0; i < length; i++) {
        cout << vr[i].name << " " << vr[i].h << " " << vr[i].m << " " << vr[i].s
             << '\n';
        newrecords << vr[i].name << " " << vr[i].h << " " << vr[i].m << " "
                   << vr[i].s << '\n';
    }
    newrecords.close();
    vr.clear();
}

void writeResult(result& r, vector<result> vr)
{
    ifstream records(
            "records.txt", ifstream::binary | ifstream::app | ifstream::in);
    for (int i = 0; i < countStr(); i++) {
        records >> r.name >> r.h >> r.m >> r.s;
        vr.push_back(r);
    }
}

/*
 *  Описание функций:
 *      - clearFile() - очищает файл для перезаписи.
 *      - countStr() - подсчёт строк в файле.
 *      - getResult(int* t, result& r, vector<result> vr){  - Сбор данных для
 * новой записи.
 *          t - время;
 *          r - структура, по которой хранятся/считываются
 * данные.
 *          vr - вектор-структура для хранения записей.
 *      }
 *      - sortResult(vector<result>& vr, int n){ - Сортировка записей по времени
 * результатов.
 *          vr - вектор-структура для хранения записей.
 *          n - размер вектор-структуры.
 *      }
 *      - rewriteResult(result& r, vector<result> vr){  - Перезапись данных.
 *          r - структура для записей.
 *          vr - вектор-структура для записей.
 *      }
 *      - writeResult(){
 *          r - структура для записей.
 *          vr - вектор-структура для записей.
 *      }
 */
