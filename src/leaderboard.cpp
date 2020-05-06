#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct result {
    string name;
    int h;
    int m;
    int s;
} r;

void getResult(int* t)
{
    fstream records("records.txt", ios::app | fstream::out | fstream::in);
    string name;
    if (records) {
        do {
            cout << "Введите имя: ";
            cin >> name;
            if (!(name.length() > 2 && name.length() < 11)) // Флаг длины имени
                cout << "\nИмя не подходит под условия:\nДлина не менее 3 и не "
                        "более 10 символов!\n";
        } while (!(name.length() > 2 && name.length() < 11));
        records << name << " " << t[0] << " " << t[1] << " " << t[2]
                << '\n'; // Запись в файл: Имя и время через пробелы
    } else {
        cout << "\nФайл не найден.\n";
    }
    records.close();
}

void sortResult()
{
    fstream records("records.txt", ios::app | fstream::out | fstream::in);
    int count = 0;
    char* str = new char[500];
    while (records) {
        records.getline(str, 500);
        count++;
    }
    delete[] str;
    count--; // Убираем фактически пустую строку.

    result* data = new result[count];
    string buffer;
    for (int i = 0; i < count; i++) {
        getline(records, buffer);
        r.name = buffer;
        buffer.clear();
        // Т.к. getline считывает до пробела, то используем getline.
        getline(records, buffer);
        // atoi - переводит из string в int.
        r.h = atoi(buffer.c_str());
        getline(records, buffer);
        r.s = atoi(buffer.c_str());
        buffer.clear();
        getline(records, buffer);
        r.s = atoi(buffer.c_str());
        buffer.clear();
        data[i] = r;
        // Но выводит всё равно нули, а имя - пустое.
        cout << data[i].name << data[i].h << data[i].m << data[i].s << endl;
    }
    cout << endl;
    // Здесь сортировка будет, но сначала решить проблему с записью в структуру.
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (data[i].h > data[j].h) {
                swap(data[i].name, data[j].name);
                swap(data[i].h, data[j].h);
                swap(data[i].m, data[j].m);
                swap(data[i].s, data[j].s);
            } else {
                if (data[i].m > data[j].m) {
                    swap(data[i].name, data[j].name);
                    swap(data[i].h, data[j].h);
                    swap(data[i].m, data[j].m);
                    swap(data[i].s, data[j].s);
                } else {
                    if (data[i].s > data[j].s) {
                        swap(data[i].name, data[j].name);
                        swap(data[i].h, data[j].h);
                        swap(data[i].m, data[j].m);
                        swap(data[i].s, data[j].s);
                    }
                }
            }
        }
    }
    delete[] data;
    records.close();
}
// Просто для тестов.
int main()
{
    // Сначала вводится время, а потом как в функциях.
    int t[3];
    cin >> t[0] >> t[1] >> t[2];
    cout << endl;
    getResult(t);
    sortResult();
}
