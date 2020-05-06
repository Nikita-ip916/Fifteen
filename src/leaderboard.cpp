#include <fstream>
#include <iostream>
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
    fstream records("records.txt", ios::app | fstream::out);
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
    fstream records("records.txt", ios::app | fstream::out);
    int count = 0;
    string name;
    char* str = new char[512];
    /* Подсчёт строк.
     *
     * Проблема: считывает до символа '\n', а не до конца файла.
     *
     */
    while (!records.eof()) {
        records.getline(str, 512, '\n');
        count++;
    }
    delete str;

    result* data = new result[count];
    for (int i = 0; i < count; i++) {
        records >> r.name >> r.h >> r.m >> r.s;
        data[i] = r;
    }
    cout << endl;
    for (int i = 0; i < count; i++) {
        cout << data[i].name << data[i].h << data[i].m
             << data[i].s; // Выводит нули, имя - пустое. Вывод: Не записывается
                           // в структуру
    }

    cout << endl;
    // Здесь сортировка будет, но сначала решить проблему с записью в структуру.
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (data[i].h > data[j].h) {
                swap(data[i].h, data[j].h);
            } else {
                if (data[i].m > data[j].m) {
                    swap(data[i].m, data[j].m);
                } else {
                    if (data[i].s > data[j].s) {
                        swap(data[i].s, data[j].s);
                    }
                }
            }
        }
    }
    delete[] data;
    // Здесь будем убирать лишние результаты.
    if (count > 5) {
        result* newData = new result[5];
        for (int i = 0; i < count; i++) {
            cin >> r.name >> r.h >> r.m >> r.s;
            data[i] = r;
        }
        records.close();
        fstream records("records.txt", ios::trunc);
        for (int i = 0; i < count; i++) {
            records << data[i].name << data[i].h << data[i].m << data[i].s
                    << '\n';
        }
        delete[] newData;
    }
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
