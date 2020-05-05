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
    void test_init_dinamic_matrix(void)
    {
        for (int i = 0; i < n; i++) {
            arr[i] = new int[n];
            exp[i] = new int[n];
        }
    }
    void test_left_correctL(void)
    {
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
    void test_left_correctR(void)
    {
        dir = 1;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        arr[1][1] = exp[1][1] = arr[1][3];
        arr[1][3] = exp[1][3] = 0;
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
    }
    void test_left_wrongL(void)
    {
        dir = 1;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    void test_right_correctL(void)
    {
        dir = 2;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
        dir = 2;
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
        exp[1][4] = arr[1][3];
        exp[1][3] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_right_wrongL(void)
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
    void test_right_wrongR(void)
    {
        dir = 2;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    }
    void test_up_correctU(void)
    {
        dir = 3;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        mas[0] = mas[1] = 1;
        exp[1][1] = arr[2][1];
        exp[2][1] = 0;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
    void test_up_correctD(void)
    {
        dir = 3;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    }
    void test_up_wrongU(void)
    {
        dir = 3;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
        dir = 3;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    }
    void test_down_correctU(void)
    {
        dir = 4;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
        dir = 4;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    }
    void test_down_wrongU(void)
    {
        dir = 4;
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
    void test_down_wrongD(void)
    {
        dir = 4;
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                arr[i][j] = j + 4 * (i - 1) - 1;
                exp[i][j] = j + 4 * (i - 1) - 1;
            }
        }
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
    }
};
