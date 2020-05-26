#include "gen.hpp"
#include <cstdlib>
#include <ctime>
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;

class GenTest : public CxxTest::TestSuite {
    const int boardSize = 5;
    int elemPresence[16], chaosIndex, expIndex;
    int** gameBoard = new int*[boardSize];

public:
    void test_init_dinamic_matrix(void)
    {
        for (int i = 0; i < boardSize; i++) {
            gameBoard[i] = new int[boardSize];
        }
    }
    void test_gen(void)
    {
        for (int i = 0; i < 16; i++) {
            elemPresence[i] = 0;
        }
        srand(time(0));
        generateArray(gameBoard, boardSize);
        for (int i = 1; i < boardSize; i++) {
            for (int j = 1; j < boardSize; j++) {
                switch (gameBoard[i][j]) {
                case 0:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 1:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 2:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 3:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 4:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 5:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 6:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 7:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 8:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 9:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 10:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 11:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 12:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 13:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 14:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                case 15:
                    elemPresence[gameBoard[i][j]] += 1;
                    break;
                }
            }
        }
        for (int i = 0; i < 16; i++) {
            TS_ASSERT_EQUALS(1, elemPresence[i]); // 1 - элемент присутствует,
        } // 0 - элемент отсутствует(ошибка),
    }     // >1 - элементов несколько(ошибка).
    void test_check_gen_correct(void)
    {
        for (int i = 1; i < boardSize; i++) { // Создание решаемой комбинации
            for (int j = 1; j < boardSize;
                 j++) { // эквивалентной всем остальным
                gameBoard[i][j] = j + 4 * (i - 1); // решаемым
                if (j + 4 * (i - 1) == 16) {
                    gameBoard[i][j] = 0;
                }
            }
        }
        chaosIndex = checkGeneration(gameBoard, boardSize);
        expIndex = 0;
        TS_ASSERT_EQUALS(expIndex, chaosIndex % 2);
    }
    void test_check_gen_wrong(void)
    {
        gameBoard[4][2]
                = 15; // Создание нерешаемой комбинации эквивалентной всем
        gameBoard[4][3] = 14; // остальным нерешаемым
        chaosIndex = checkGeneration(gameBoard, boardSize);
        expIndex = 1;
        TS_ASSERT_EQUALS(expIndex, chaosIndex % 2);
    }
};
