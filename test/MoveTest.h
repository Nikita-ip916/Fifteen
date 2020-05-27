#include "move.hpp"
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;

class MoveTest : public CxxTest::TestSuite {
    const int boardSize = 5;
    int emptyElem[2];
    int dir, i, j;
    int **gameBoard = new int *[boardSize],
        **expGameBoard = new int *[boardSize];

public:
    void testInitDinamicMatrix(void)
    {
        for (int i = 0; i < boardSize; i++) {
            gameBoard[i] = new int[boardSize];
            expGameBoard[i] = new int[boardSize];
        }
    }
    void testLeftCorrectL(void) // леваяКлавиша_правильныйХод_леваяГрЭквив
    {
        dir = 1;
        for (i = 1; i < boardSize; i++) { // Исходное упорядочивание матрицы
            for (j = 1; j < boardSize; j++) { // в порядке от 0 до 15
                gameBoard[i][j] = j + 4 * (i - 1) - 1;
                expGameBoard[i][j] = j + 4 * (i - 1) - 1;
            }
        }
        emptyElem[0] = emptyElem[1] = 1;
        expGameBoard[1][2] = 0; // Ожидаемое выполнение хода
        expGameBoard[1][1] = gameBoard[1][2]; //
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[1][2] = expGameBoard[1][2]
                = expGameBoard[1][1];             // Возвращение
        gameBoard[1][1] = expGameBoard[1][1] = 0; // к исходному порядку
    }
    void testLeftCorrectR(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[1][3]; // Перемещение
        gameBoard[1][3] = expGameBoard[1][3]
                = 0; // пустого элемента в правую ГрЭквив
        emptyElem[0] = 1;
        emptyElem[1] = 3;
        expGameBoard[1][4] = 0;
        expGameBoard[1][3] = gameBoard[1][4];
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[1][4] = expGameBoard[1][4] = expGameBoard[1][3];
        gameBoard[1][3] = expGameBoard[1][3] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testLeftWrongL(void) // леваяКлавиша_ходВнеГраницПоля_леваяГрЭквив
    {
        emptyElem[0] = 1;
        emptyElem[1] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
    }
    void testLeftWrongR(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[1][4];
        gameBoard[1][4] = expGameBoard[1][4] = 0;
        emptyElem[0] = 1;
        emptyElem[1] = 4;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[1][4] = expGameBoard[1][4] = gameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testRightCorrectL(void) // праваяКлавиша_правильныйХод_леваяГрЭквив
    {
        dir = 2;
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[1][2];
        gameBoard[1][2] = expGameBoard[1][2] = 0;
        emptyElem[0] = 1;
        emptyElem[1] = 2;
        expGameBoard[1][2] = gameBoard[1][1];
        expGameBoard[1][1] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
    }
    void testRightCorrectR(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[1][4];
        gameBoard[1][4] = expGameBoard[1][4] = 0;
        emptyElem[0] = 1;
        emptyElem[1] = 4;
        expGameBoard[1][4] = gameBoard[1][3];
        expGameBoard[1][3] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[1][3] = expGameBoard[1][3] = expGameBoard[1][4];
        gameBoard[1][4] = expGameBoard[1][4] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testRightWrongL(void)
    {
        emptyElem[0] = emptyElem[1] = 1;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
    }
    void testRightWrongR(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[1][4];
        gameBoard[1][4] = expGameBoard[1][4] = 0;
        emptyElem[0] = 1;
        emptyElem[1] = 5;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[1][4] = expGameBoard[1][4] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testUpCorrectU(void) // верхняяКлавиша_правильныйХод_верхняяГрЭквив
    {
        dir = 3;
        emptyElem[0] = emptyElem[1] = 1;
        expGameBoard[1][1] = gameBoard[2][1];
        expGameBoard[2][1] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[2][1] = expGameBoard[2][1] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testUpCorrectD(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[3][1];
        gameBoard[3][1] = expGameBoard[3][1] = 0;
        emptyElem[0] = 3;
        emptyElem[1] = 1;
        expGameBoard[3][1] = gameBoard[4][1];
        expGameBoard[4][1] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[4][1] = expGameBoard[4][1] = expGameBoard[3][1];
        gameBoard[3][1] = expGameBoard[3][1] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testUpWrongU(void)
    {
        emptyElem[0] = 0;
        emptyElem[1] = 1;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
    }
    void testUpWrongD(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[4][1];
        gameBoard[4][1] = expGameBoard[4][1] = 0;
        emptyElem[0] = 4;
        emptyElem[1] = 1;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[4][1] = expGameBoard[4][1] = gameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testDownCorrectU(void) // нижняяКлавиша_правильныйХод_верхняяГрЭквив
    {
        dir = 4;
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[2][1];
        gameBoard[2][1] = expGameBoard[2][1] = 0;
        emptyElem[0] = 2;
        emptyElem[1] = 1;
        expGameBoard[2][1] = gameBoard[1][1];
        expGameBoard[1][1] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
    }
    void testDownCorrectD(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[4][1];
        gameBoard[4][1] = expGameBoard[4][1] = 0;
        emptyElem[0] = 4;
        emptyElem[1] = 1;
        expGameBoard[4][1] = gameBoard[3][1];
        expGameBoard[3][1] = 0;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[3][1] = expGameBoard[3][1] = expGameBoard[4][1];
        gameBoard[4][1] = expGameBoard[4][1] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
    void testDownWrongU(void)
    {
        emptyElem[0] = emptyElem[1] = 1;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
    }
    void testDownWrongD(void)
    {
        gameBoard[1][1] = expGameBoard[1][1] = gameBoard[4][1];
        gameBoard[4][1] = expGameBoard[4][1] = 0;
        emptyElem[0] = 5;
        emptyElem[1] = 1;
        moveF(dir, gameBoard, boardSize, emptyElem);
        for (i = 1; i < boardSize; i++) {
            for (j = 1; j < boardSize; j++) {
                TS_ASSERT_EQUALS(expGameBoard[i][j], gameBoard[i][j]);
            }
        }
        gameBoard[4][1] = expGameBoard[4][1] = expGameBoard[1][1];
        gameBoard[1][1] = expGameBoard[1][1] = 0;
    }
};
