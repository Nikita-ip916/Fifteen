#include "gen.hpp"
#include <cstdlib>
#include <ctime>
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;

class GenTest : public CxxTest::TestSuite {
    const int n = 5;
    int a[16], chaos_index, exp_index; // a - 'отмечает' присутствие i-го
    int** arr = new int*[n]; // элемента в матрице

public:
    void test_init_dinamic_matrix(void)
    {
        for (int i = 0; i < n; i++) {
            arr[i] = new int[n]; // Реальная матрица
        }
    }
    void test_gen(void)
    {
        for (int i = 0; i < 16; i++) {
            a[i] = 0;
        }
        srand(time(0));
        generateArray(arr, n);
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                switch (arr[i][j]) {
                case 0:
                    a[arr[i][j]] = 1;
                    break;
                case 1:
                    a[arr[i][j]] = 1;
                    break;
                case 2:
                    a[arr[i][j]] = 1;
                    break;
                case 3:
                    a[arr[i][j]] = 1;
                    break;
                case 4:
                    a[arr[i][j]] = 1;
                    break;
                case 5:
                    a[arr[i][j]] = 1;
                    break;
                case 6:
                    a[arr[i][j]] = 1;
                    break;
                case 7:
                    a[arr[i][j]] = 1;
                    break;
                case 8:
                    a[arr[i][j]] = 1;
                    break;
                case 9:
                    a[arr[i][j]] = 1;
                    break;
                case 10:
                    a[arr[i][j]] = 1;
                    break;
                case 11:
                    a[arr[i][j]] = 1;
                    break;
                case 12:
                    a[arr[i][j]] = 1;
                    break;
                case 13:
                    a[arr[i][j]] = 1;
                    break;
                case 14:
                    a[arr[i][j]] = 1;
                    break;
                case 15:
                    a[arr[i][j]] = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < 16; i++) {
            TS_ASSERT_EQUALS(1, a[i]); // 1 - элемент присутствует,
        } // 0 - элемент отсутствует(ошибка),
    }     // >1 - элементов несколько(ошибка).
    void test_check_gen_correct(void)
    {
        for (int i = 1; i < n; i++) { // Создание решаемой комбинации
            for (int j = 1; j < n; j++) { // эквивалентной всем остальным
                arr[i][j] = j + 4 * (i - 1); // решаемым
                if (j + 4 * (i - 1) == 16) {
                    arr[i][j] = 0;
                }
            }
        }
        chaos_index = checkGeneration(arr, n);
        exp_index = 0;
        TS_ASSERT_EQUALS(exp_index, chaos_index % 2);
    }
    void test_check_gen_wrong(void)
    {
        arr[4][2] = 15; // Создание нерешаемой комбинации эквивалентной всем
        arr[4][3] = 14; // остальным нерешаемым
        chaos_index = checkGeneration(arr, n);
        exp_index = 1;
        TS_ASSERT_EQUALS(exp_index, chaos_index % 2);
    }
};
