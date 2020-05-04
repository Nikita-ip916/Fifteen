#include "move.hpp"
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;
const int n = 5;

class MoveTest : public CxxTest::TestSuite {
    int mas[2];
    int dir, i, j;
    int **arr = new int *[n], **exp = new int *[n];

public:
    void test_left_correct(void)
    {
        for (i = 0; i < n; i++) {
            arr[i] = new int[n];
            exp[i] = new int[n];
        }
        dir = 1;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        mas[0] = mas[1] = 1;
        exp[1][2] = 0;
        exp[1][1] = arr[1][2];
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_left_wrong(void)
    {
        dir = 1;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    }
    void test_right_correct(void)
    {
        dir = 2;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        arr[1][1] = exp[1][1] = arr[2][3];
        arr[2][3] = exp[2][3] = 0;
        mas[0] = 2;
        mas[1] = 3;
        exp[2][3] = arr[2][2];
        exp[2][2] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_right_wrong(void)
    {
        dir = 2;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        mas[0] = mas[1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
};
