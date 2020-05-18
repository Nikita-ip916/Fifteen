#include "move.hpp"
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;

class MoveTest : public CxxTest::TestSuite {
    const int n = 5;
    int mas[2]; // Координаты пустой клетки перед ходом
    int dir, i, j; // dir - направление хода
    int **arr = new int *[n], **exp = new int *[n];

public:
    void test_init_dinamic_matrix(void)
    {
        for (int i = 0; i < n; i++) {
            arr[i] = new int[n]; // Реальная матрица
            exp[i] = new int[n]; // Ожидаемая матрица
        }
    }
    void test_left_correctL(void) // леваяКлавиша_правильныйХод_леваяГрЭквив
    {
        dir = 1;
        for (i = 1; i < n; i++) { // Исходное упорядочивание матрицы
            for (j = 1; j < n; j++) { // в порядке от 0 до 15
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        mas[0] = mas[1] = 1; // Пустая клетка в первой строке первом столбце
        exp[1][2] = 0;       // Ожидаемое выполнение хода
        exp[1][1] = arr[1][2]; //
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[1][2] = exp[1][2] = exp[1][1]; // Возвращение к исходному порядку
        arr[1][1] = exp[1][1] = 0; //
    }
    void test_left_correctR(void)
    {
        arr[1][1] = exp[1][1] = arr[1][3]; // Перемещение пустого элемента в
        arr[1][3] = exp[1][3] = 0; // правую ГрЭквив
        mas[0] = 1;
        mas[1] = 3;
        exp[1][4] = 0;
        exp[1][3] = arr[1][4];
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[1][4] = exp[1][4] = exp[1][3];
        arr[1][3] = exp[1][3] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_left_wrongL(void) // леваяКлавиша_ходВнеГраницПоля_леваяГрЭквив
    {
        mas[0] = 1;
        mas[1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_left_wrongR(void)
    {
        arr[1][1] = exp[1][1] = arr[1][4];
        arr[1][4] = exp[1][4] = 0;
        mas[0] = 1;
        mas[1] = 4;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[1][4] = exp[1][4] = arr[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_right_correctL(void) // праваяКлавиша_правильныйХод_леваяГрЭквив
    {
        dir = 2;
        arr[1][1] = exp[1][1] = arr[1][2];
        arr[1][2] = exp[1][2] = 0;
        mas[0] = 1;
        mas[1] = 2;
        exp[1][2] = arr[1][1];
        exp[1][1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_right_correctR(void)
    {
        arr[1][1] = exp[1][1] = arr[1][4];
        arr[1][4] = exp[1][4] = 0;
        mas[0] = 1;
        mas[1] = 4;
        exp[1][4] = arr[1][3];
        exp[1][3] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[1][3] = exp[1][3] = exp[1][4];
        arr[1][4] = exp[1][4] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_right_wrongL(void)
    {
        mas[0] = mas[1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_right_wrongR(void)
    {
        arr[1][1] = exp[1][1] = arr[1][4];
        arr[1][4] = exp[1][4] = 0;
        mas[0] = 1;
        mas[1] = 5;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[1][4] = exp[1][4] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_up_correctU(void) // верхняяКлавиша_правильныйХод_верхняяГрЭквив
    {
        dir = 3;
        mas[0] = mas[1] = 1;
        exp[1][1] = arr[2][1];
        exp[2][1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[2][1] = exp[2][1] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_up_correctD(void)
    {
        arr[1][1] = exp[1][1] = arr[3][1];
        arr[3][1] = exp[3][1] = 0;
        mas[0] = 3;
        mas[1] = 1;
        exp[3][1] = arr[4][1];
        exp[4][1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[4][1] = exp[4][1] = exp[3][1];
        arr[3][1] = exp[3][1] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_up_wrongU(void)
    {
        mas[0] = 0;
        mas[1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_up_wrongD(void)
    {
        arr[1][1] = exp[1][1] = arr[4][1];
        arr[4][1] = exp[4][1] = 0;
        mas[0] = 4;
        mas[1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[4][1] = exp[4][1] = arr[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_down_correctU(void) // нижняяКлавиша_правильныйХод_верхняяГрЭквив
    {
        dir = 4;
        arr[1][1] = exp[1][1] = arr[2][1];
        arr[2][1] = exp[2][1] = 0;
        mas[0] = 2;
        mas[1] = 1;
        exp[2][1] = arr[1][1];
        exp[1][1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_down_correctD(void)
    {
        arr[1][1] = exp[1][1] = arr[4][1];
        arr[4][1] = exp[4][1] = 0;
        mas[0] = 4;
        mas[1] = 1;
        exp[4][1] = arr[3][1];
        exp[3][1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[3][1] = exp[3][1] = exp[4][1];
        arr[4][1] = exp[4][1] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
    void test_down_wrongU(void)
    {
        mas[0] = mas[1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_down_wrongD(void)
    {
        arr[1][1] = exp[1][1] = arr[4][1];
        arr[4][1] = exp[4][1] = 0;
        mas[0] = 5;
        mas[1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
        arr[4][1] = exp[4][1] = exp[1][1];
        arr[1][1] = exp[1][1] = 0;
    }
};
