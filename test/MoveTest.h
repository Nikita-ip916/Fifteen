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
        exp[1][1] = 1;
        moveF(dir, arr, n, mas);
        for (i = 1; i < n; i++) {
            for (j = 1; j < n; j++) {
                TS_ASSERT_EQUALS(exp[i][j], arr[i][j]);
            }
        }
    }
};
