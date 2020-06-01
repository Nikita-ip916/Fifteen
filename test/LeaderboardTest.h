#include "leaderboard.hpp"
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Result {
    string name;
    int hours;
    int minutes;
    int seconds;
} result;

class LeaderboardTest : public CxxTest::TestSuite {
    vector<Result> expVectorResult;
    vector<Result> vectorResult;

public:
    void testSortNoRepetition(void)
    {
        expVectorResult
                = {{"First", 0, 0, 50},
                   {"Second", 0, 0, 51},
                   {"Third", 0, 1, 50},
                   {"Fourth", 0, 1, 51},
                   {"Fifth", 1, 0, 50},
                   {"Sixth", 1, 0, 51}};
        vectorResult
                = {{"Sixth", 1, 0, 51},
                   {"Third", 0, 1, 50},
                   {"Fifth", 1, 0, 50},
                   {"First", 0, 0, 50},
                   {"Fourth", 0, 1, 51},
                   {"Second", 0, 0, 51}};
        int length = vectorResult.size();
        int* indexArray = new int[length];
        for (int i = 0; i < length; i++) {
            indexArray[i] = i;
        }
        sortResult(indexArray, vectorResult, length);
        for (int i = 0; i < length; i++) {
            TS_ASSERT_EQUALS(
                    expVectorResult[i].name, vectorResult[indexArray[i]].name);
            TS_ASSERT_EQUALS(
                    expVectorResult[i].hours,
                    vectorResult[indexArray[i]].hours);
            TS_ASSERT_EQUALS(
                    expVectorResult[i].minutes,
                    vectorResult[indexArray[i]].minutes);
            TS_ASSERT_EQUALS(
                    expVectorResult[i].seconds,
                    vectorResult[indexArray[i]].seconds);
        }
        delete[] indexArray;
    }
    void testSortWithRepetition(void)
    {
        result.name = "ThirdOther";
        result.seconds = 50;
        result.minutes = 1;
        result.hours = 0;
        vectorResult.push_back(result);
        expVectorResult.insert(expVectorResult.begin() + 3, result);
        int length = vectorResult.size();
        int* indexArray = new int[length];
        for (int i = 0; i < length; i++) {
            indexArray[i] = i;
        }
        sortResult(indexArray, vectorResult, length);
        for (int i = 0; i < length; i++) {
            TS_ASSERT_EQUALS(
                    expVectorResult[i].name, vectorResult[indexArray[i]].name);
            TS_ASSERT_EQUALS(
                    expVectorResult[i].hours,
                    vectorResult[indexArray[i]].hours);
            TS_ASSERT_EQUALS(
                    expVectorResult[i].minutes,
                    vectorResult[indexArray[i]].minutes);
            TS_ASSERT_EQUALS(
                    expVectorResult[i].seconds,
                    vectorResult[indexArray[i]].seconds);
        }
        delete[] indexArray;
    }
    void testCheckNameBorder(void)
    {
        char data[12] // Символы с граничными значениями. 6 неверных и 6 верных
                      // соответственно
                = {'/', ':', '@', '[', '`', '{', '0', '9', 'A', 'Z', 'a', 'z'};
        for (int i = 0; i < 12; i++) {
            result.name = string(4, data[i]);
            if (i < 6) {
                TS_ASSERT_EQUALS(checkName(result), 0);
            } else {
                TS_ASSERT_EQUALS(checkName(result), 1);
            }
            result.name = "";
        }
    }
    void testCheckNameLength(void)
    {
        result.name = "TooLongName";
        TS_ASSERT_EQUALS(checkName(result), 0);
        result.name = "NormalName";
        TS_ASSERT_EQUALS(checkName(result), 1);
    }
};
